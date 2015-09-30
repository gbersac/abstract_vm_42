#include <fstream>
#include <string>
#include <cerrno>

#include "Stack.hpp"
#include "Operand.hpp"
#include "parse.hpp"

std::string getFileContent(const char *filename)
{
	std::ifstream in(filename, std::ios::in);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

std::string getStdinContent()
{
	std::stringstream ss;
	for (std::string line; std::getline(std::cin, line);) {
		if (line == ";;")
			return ss.str();
		ss << std::endl << line;
    }
	return ss.str();
}

void		printInstructions(std::vector<IInstruction*> instructions)
{
	std::vector<IInstruction*>::iterator i;
	for (i = instructions.begin() ; i != instructions.end() ; ++i) {
		std::cout << (*i)->toString() << " ";
	}
}

int			executeVM(std::string content)
{
	// std::cout << content << std::endl;
	std::vector<IInstruction*> instructions = parse(content);
	if (!hasParseError(-1))
		printInstructions(instructions); std::cout << std::endl;
		//run
	return (0);
}

int			main(int argc, char const *argv[])
{
	if (argc == 1) {
		std::string content = getStdinContent();
		executeVM(content);
	} else {
		int i = 1;
		while (i < argc) {
			std::string content;
			std::cout << "For file: \033[1;32m" << argv[i] << "\033[0m" << std::endl;
			try {
				content = getFileContent(argv[i]);
				executeVM(content);
			} catch (int& e) {
				std::cout << "Can't read file " << argv[i] << std::endl;
			}
			std::cout << std::endl;
			++i;
		}
	}
	return 0;
}
