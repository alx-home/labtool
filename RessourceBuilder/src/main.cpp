/*
 * main.cpp
 *
 *  Created on: 22 janv. 2016
 *      Author: Alexandre GARCIN
 */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <windows.h>

template<typename Type>
class FileAllocator {
public:
	FileAllocator(Type& file, const std::string& filePath, std::ios_base::openmode flags) :
			file(file) {
		file.open(filePath, flags);

		if (!file || file.fail())
			throw std::exception();
	}

	virtual ~FileAllocator() {
		if (file)
			file.close();
	}

private:
	Type& file;
};

int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 4) {
		std::cerr << "\nUsage: ressourceBuilder fileName className [currentDir]" << std::endl;
		return EXIT_FAILURE;
	}

	std::string fileName = argv[1];
	std::string className = argv[2];
	std::string classNameUpper;
	std::string currentSrcDir = "";

	if (argc == 4) {
		currentSrcDir = argv[3];
		currentSrcDir += "/";
	}

	std::locale loc;
	for (std::string::size_type i = 0; i < className.length(); ++i)
		classNameUpper += std::toupper(className[i], loc);

	std::cout << "\n[RessourceBuilder]Generating : " << className << ", from : " << fileName << "." << std::endl;

	std::ifstream inputFile;
	std::ofstream outputFile;

	try {
		std::unique_ptr<FileAllocator<std::ifstream>> inputFileAllocator = std::unique_ptr<FileAllocator<std::ifstream>>(
				new FileAllocator<std::ifstream>(inputFile, currentSrcDir + "resources/files/" + fileName, std::ios::in | std::ios::binary));

		unsigned int fileSize = 0;
		inputFile.seekg(0, std::ios::end);
		fileSize = inputFile.tellg();
		inputFile.seekg(0, std::ios::beg);

		try {
			std::unique_ptr<FileAllocator<std::ofstream>> outputFileAllocator = std::unique_ptr<FileAllocator<std::ofstream>>(
					new FileAllocator<std::ofstream>(outputFile, currentSrcDir + "resources/classes/" + className + ".h", std::ios::out));

			outputFile << "#ifndef SRC_RESOURCES_" << classNameUpper << "_H_\n" << "#define SRC_RESOURCES_" << classNameUpper << "_H_\n\n"
					<< "#include <array>\n" << "#include <cstdint>\n\n" << "namespace resources {\n\n" << "class  " << className << " {\n"
					<< "public:\n\t" << className << "() = delete;\n" << "\tvirtual ~" << className << "() = delete;\n\n"
					<< "\tstatic std::array<uint8_t, " << std::to_string(fileSize)
					<< "> datas;\n};\n\n} /* namespace resources */\n\n#endif  /* SRC_RESOURCES_" << classNameUpper << "_H_ */\n";
		} catch (...) {
			std::cerr << "\n[RessourceBuilder][ERROR]impossible de créer le fichier header : " << className << ".h .\n" << std::endl;
			return EXIT_FAILURE;
		}

		try {
			std::unique_ptr<FileAllocator<std::ofstream>> outputFileAllocator = std::unique_ptr<FileAllocator<std::ofstream>>(
					new FileAllocator<std::ofstream>(outputFile, currentSrcDir + "resources/classes/" + className + ".cpp", std::ios::out));

			outputFile << "\n#include \"" << className << ".h\"\n\nnamespace resources {\n\nstd::array<uint8_t, "
					<< std::to_string(fileSize) << "> " << className << "::datas = {\n\t";

			unsigned int index = 1;
			char buff = inputFile.get();

			outputFile << "0x" << std::hex << (int)static_cast<unsigned char>(buff);

			while (!inputFile.eof()) {
				buff = inputFile.get();

				if (!inputFile)
					break;

				outputFile << (index == 0 ? ",\n\t" : ", ") << "0x" << std::hex << (int)static_cast<unsigned char>(buff);

				++index;
				index %= 20;

			}

			outputFile << "\n};\n\n} /* namespace ressources */" << std::endl;
		} catch (...) {
			std::cerr << "[RessourceBuilder][ERROR]impossible de créer le fichier source : " << className << ".cpp .\n" << std::endl;
			return EXIT_FAILURE;
		}
	} catch (...) {
		std::cerr << "\n[RessourceBuilder][ERROR]impossible d'ouvrir le fichier d'entré : " << fileName << ".\n" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "\nResourceFile succefully generated !\n" << std::endl;
}
