/*
 * CoutMatlab.h
 *
 *  Created on: 22 déc. 2015
 *      Author: Alexandre GARCIN
 */

#ifndef SRC_COUTMATLAB_H_
#define SRC_COUTMATLAB_H_

#include <iostream>
#include <fstream>
#include <memory>

namespace generic {

class StreamRedirect {
public:
	StreamRedirect(std::ostream& stream, std::streambuf* rdbuf);
	virtual ~StreamRedirect();

private:
	StreamRedirect(const StreamRedirect&) = delete;
	StreamRedirect& operator =(const StreamRedirect&) = delete;

	std::ostream& stream;
	std::streambuf* rdbuf_old;
};

class StreamRedirectBuff: public std::streambuf {
public:
	StreamRedirectBuff(const std::string& name, const std::string& extension);
	virtual ~StreamRedirectBuff();

protected:
	std::string path;
	char buffer[8192];
	std::string name;
	std::ofstream file;

	virtual int_type overflow(int_type c) override;
	virtual int_type sync() override;
};

class cerrBuf: public StreamRedirectBuff {
public:
	cerrBuf(const std::string& name);
	virtual ~cerrBuf();

private:
	bool isEmpty = true;
	virtual int_type sync() override;
};

class coutBuf: public StreamRedirectBuff {
public:
	coutBuf(const std::string& name);
	virtual ~coutBuf();

protected:
	virtual int_type sync() override;
};

class clogBuf: public StreamRedirectBuff {
public:
	clogBuf(const std::string& name);
	virtual ~clogBuf();

protected:
	virtual int_type sync() override;
};

class coutRedirect: private virtual coutBuf, public std::ostream {
private:
	StreamRedirect streamRedirect;

public:
	coutRedirect(const std::string& name);
	virtual ~coutRedirect();
};

class clogRedirect: private virtual clogBuf, public std::ostream {
private:
	StreamRedirect streamRedirect;

public:
	clogRedirect(const std::string& name);
	virtual ~clogRedirect();
};

class cerrRedirect: private virtual cerrBuf, public std::ostream {
private:
	StreamRedirect streamRedirect;

public:
	cerrRedirect(const std::string& name);
	virtual ~cerrRedirect();
};
}  // namespace generic

#endif /* SRC_COUTMATLAB_H_ */
