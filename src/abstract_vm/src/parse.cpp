#include "parse.hpp"

/**
 * Test if the string begin by a separator and delete them all.
 * Return true if the string have at least one separator.
 */
bool separator(std::string &str)
{
	bool	hasSeparator;

	while (str.size() > 0 && (str[0] == ' ' || str[0] == '\t')) {
		hasSeparator = true;
		str.erase(0, 1);
	}
	return hasSeparator;
}

bool isComment(std::string &str)
{
	if (str[0] == ';')
		return true;
	return false;
}

bool isInstruction(std::string instr, std::string &str)
{
	if (str.compare(0, instr.size(), instr) != 0)
		return false;
	std::string cpy = std::string(str);
	cpy.erase(0, instr.size());
	separator(cpy);
	if (cpy.size() == 0 || isComment(cpy))
		return true;
	return false;
}

const IOperand* isOperand(std::string &str)
{
	//check global
	static std::regex reg1("[a-z0-9]+\\([-]?[0-9]+.?[0-9]*e?[+-]?[0-9]*\\).*");
	if (!std::regex_match(str, reg1))
		return NULL;

	//check if type name is correct
	std::size_t found = str.find("(");
	if (found == std::string::npos)
		return NULL;
	std::string typeName = str.substr(0, found);
	eOperandType type = operandTypeFromString(typeName);
	if (type == UNKNOW)
		return NULL;

	//check for the number
	std::smatch m;
	if (type == DOUBLE || type == FLOAT){
		static std::regex regFloat("[a-z0-9]+\\(([-]?[0-9]+.?[0-9]*e?[+-]?[0-9]*)\\).*");
		std::regex_search(str, m, regFloat);
		return IOperand::createOperand(type, m[1]);
	} else {
		static std::regex regInt("[a-z0-9]+\\(([-]?[0-9]+)\\).*");
		std::regex_search(str, m, regInt);
		return IOperand::createOperand(type, m[1]);
	}
}

const IOperand* isRichInstruction(std::string instr, std::string &str)
{
	// check instruction name
	if (str.compare(0, instr.size(), instr) != 0)
		return NULL;
	std::string cpy = std::string(str);
	cpy.erase(0, instr.size());

	//check if instruction name is followed by an operand
	if (!separator(cpy))
		return NULL;
	const IOperand* value = isOperand(cpy);
	if (value == NULL)
		return NULL;

	//check the end of instruction
	std::size_t found = cpy.find(")");
	if (found == std::string::npos)
		return NULL;
	cpy.erase(0, found + 1);
	separator(cpy);
	if (cpy.size() == 0 || isComment(cpy))
		return value;
	return NULL;
}

IInstruction* isPush(std::string &str)
{
	const IOperand* op = isRichInstruction("push", str);
	if (op == NULL)
		return NULL;
	return new InstrPush(op);
}

IInstruction* isAssert(std::string &str)
{
	const IOperand* op = isRichInstruction("assert", str);
	if (op == NULL)
		return NULL;
	return new InstrAssert(op);
}

IInstruction* isPop(std::string &str)
{
	if (!isInstruction("pop", str))
		return NULL;
	return new InstrPop();
}

IInstruction* isDump(std::string &str)
{
	if (!isInstruction("dump", str))
		return NULL;
	return new InstrDump();
}

IInstruction* isAdd(std::string &str)
{
	if (!isInstruction("add", str))
		return NULL;
	return new InstrAdd();
}

IInstruction* isSub(std::string &str)
{
	if (!isInstruction("sub", str))
		return NULL;
	return new InstrSub();
}

IInstruction* isMul(std::string &str)
{
	if (!isInstruction("mul", str))
		return NULL;
	return new InstrMul();
}

IInstruction* isDiv(std::string &str)
{
	if (!isInstruction("div", str))
		return NULL;
	return new InstrDiv();
}

IInstruction* isMod(std::string &str)
{
	if (!isInstruction("mod", str))
		return NULL;
	return new InstrMod();
}

IInstruction* isPrint(std::string &str)
{
	if (!isInstruction("print", str))
		return NULL;
	return new InstrPrint();
}

IInstruction* isExit(std::string &str)
{
	if (!isInstruction("exit", str))
		return NULL;
	return new InstrExit();
}

typedef IInstruction* (*instructionTestFn)(std::string &);

IInstruction* isInstruction(std::string &str)
{
	static instructionTestFn fns[] = {isPush, isPop, isDump, isAssert, isAdd,
			isSub, isMul, isDiv, isMod, isPrint, isExit, NULL};

	for (int i = 0; fns[i] != NULL ; ++i){
		IInstruction* toReturn = fns[i](str);
		if (toReturn != NULL)
			return toReturn;
	}
	return NULL;
}

IInstruction* parseLine(std::string &line)
{
	separator(line);
	if (!(line.size() == 0 || isComment(line))){
		IInstruction* newi = isInstruction(line);
		if (newi == NULL){
			throw InvalidInstructionError();
		}
		return newi;
	}
	return NULL;
}

std::vector<IInstruction*> parse(std::string &str)
{
	std::istringstream f(str);
	std::string line;
	std::vector<IInstruction*> toReturn;
	int lineNumber = 1;
	hasParseError(0);
	while (std::getline(f, line)) {
		try {
			IInstruction* newi = parseLine(line);
			if (newi != NULL)
				toReturn.push_back(newi);
		} catch (std::exception &e) {
			std::cout << "\033[1;31mParseError line " << lineNumber << ": \033[0m"
					<< e.what() << std::endl << line  << std::endl;
				hasParseError(1);
		}
		++lineNumber;
	}
	return toReturn;
}

bool hasParseError(int set)
{
	static bool hasError = false;

	if (set == 1 || set == 0)
		hasError = set;
	return hasError;
}
