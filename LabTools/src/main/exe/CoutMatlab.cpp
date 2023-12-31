/*
 * CoutMatlab.cpp
 *
 *  Created on: 22 d�c. 2015
 *      Author: Alexandre GARCIN
 */
#ifndef MATLAB

#include <CoutMatlab.h>

#include <_mingw.h>
#include <cstdio>
#include <cwchar>
#include <iterator>
#include <windows.h>
#include <functional>
#include <string>
#include <ctime>
#include <iostream>

#include "../../utils/window/files/File.h"

namespace generic {

StreamRedirect::StreamRedirect(std::ostream& stream, std::streambuf* rdbuf) :
		stream(stream), rdbuf_old(stream.rdbuf()) {
	stream.rdbuf(rdbuf);
}

StreamRedirect::~StreamRedirect() {
	stream.rdbuf(rdbuf_old);
}

StreamRedirectBuff::StreamRedirectBuff(const std::string& name, const std::string& extension) :
		name(name), file(), path() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d_%m_%Y-%H_%M", timeinfo);

	CreateDirectory("log", nullptr);
	CreateDirectory((path = "log/" + std::string(buffer)).c_str(), nullptr);

	file.open(("log/" + std::string(buffer) + "/" + name + extension).c_str()); //todo put_time (iomanip)
	setp(this->buffer, this->buffer + sizeof(this->buffer) - 1);
}

StreamRedirectBuff::~StreamRedirectBuff() {
	if (file)
		file.close();
}

StreamRedirectBuff::int_type StreamRedirectBuff::overflow(StreamRedirectBuff::int_type c) {
	if (!traits_type::eq_int_type(c, traits_type::eof())) {
		*this->pptr() = traits_type::to_char_type(c);
		pbump(1);
	}

	return sync() ? traits_type::not_eof(c) : traits_type::eof();
}

StreamRedirectBuff::int_type StreamRedirectBuff::sync() {
	if (pbase() != pptr()) {
		std::string text(pbase(), pptr());

		{
			std::string out("[" + name + "]\n" + text + (*(text.end() - 1) == '\n' ? "" : "\n") + "[/" + name + "]\n");

			fprintf(stdout, "%s", out.c_str());
			fflush(stdout);
		}

		StreamRedirectBuff::file << text << std::flush;
		setp(pbase(), epptr());
		return 1;
	}

	return 0;
}

coutRedirect::coutRedirect(const std::string& name) :
		std::ostream(static_cast<std::streambuf*>(this)), streamRedirect(std::cout, this->rdbuf()), coutBuf(name) {
	setf(std::ios_base::unitbuf);
}

coutRedirect::~coutRedirect() {
	std::cout << std::flush;
}

clogRedirect::clogRedirect(const std::string& name) :
		std::ostream(static_cast<std::streambuf*>(this)), streamRedirect(std::clog, this->rdbuf()), clogBuf(name) {
	setf(std::ios_base::unitbuf);
}

clogRedirect::~clogRedirect() {
	std::clog << std::flush;
}

cerrRedirect::cerrRedirect(const std::string& name) :
		std::ostream(static_cast<std::streambuf*>(this)), streamRedirect(std::cerr, this->rdbuf()), cerrBuf(name) {
	setf(std::ios_base::unitbuf);
	std::cerr.unsetf(std::ios_base::unitbuf);
}

cerrRedirect::~cerrRedirect() {
	std::cerr << std::flush;
	std::cerr.setf(std::ios_base::unitbuf);
}

cerrBuf::cerrBuf(const std::string& name) :
		StreamRedirectBuff(name, ".debug") {
}

cerrBuf::~cerrBuf() {
	if (file)
		StreamRedirectBuff::file.close();

	if (isEmpty)
		try {
			utils::window::File::removeDirectory(StreamRedirectBuff::path);
		} catch (...) {
			std::cerr << "Error: fatal error occured in file : " << __FILE__ << ", at line : " << __LINE__ << "." << std::endl;
		}
}

coutBuf::coutBuf(const std::string& name) :
		StreamRedirectBuff(name, ".out") {
}

coutBuf::~coutBuf() {
	if (file)
		StreamRedirectBuff::file.close();
}

coutBuf::int_type coutBuf::sync() {
	return StreamRedirectBuff::sync();
}

clogBuf::clogBuf(const std::string& name) :
		StreamRedirectBuff(name, ".log") {
}

clogBuf::~clogBuf() {
	if (file)
		StreamRedirectBuff::file.close();
}

clogBuf::int_type clogBuf::sync() {
	if (pbase() != pptr()) {
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 80, "[%I:%M %ss]", timeinfo);

		std::string out(pbase(), pptr());
		StreamRedirectBuff::file << std::string(buffer) + out << std::flush;
		setp(pbase(), epptr());
	}

	return 0;
}

cerrBuf::int_type cerrBuf::sync() {
	if (pbase() != pptr()) {
		std::string text(pbase(), pptr());

		{
			isEmpty = false;
			std::string out = "[Error: \"" + name + "\"]\n" + text + (*(text.end() - 1) == '\n' ? "" : "\n") + "[/Error]\n";

			fprintf(stderr, "%s", out.c_str());
			fflush(stderr);
		}

		StreamRedirectBuff::file << text << std::flush;
		setp(pbase(), epptr());
	}

	return 0;
}
}  // namespace generic

#endif
