#include "Operand.hpp"

IOperand const * IOperand::createOperand(eOperandType type, std::string const & value)
{
	IOperand const * toReturn = NULL;
	switch(type){
		case INT8 :
			toReturn = IOperand::createInt8(value);
			break ;
		case INT16 :
			toReturn = IOperand::createInt16(value);
			break ;
		case INT32 :
			toReturn = IOperand::createInt32(value);
			break ;
		case FLOAT :
			toReturn = IOperand::createFloat(value);
			break ;
		case DOUBLE :
			toReturn = IOperand::createDouble(value);
			break ;
		default :
			break ;
	}
	return (toReturn);
}

IOperand const * IOperand::createInt8(std::string const & value)
{
 	int	val = std::stoi(value);
	if (val <= -128 || val >= 127)
		throw OverflowError();
	return (new Operand<int8_t>(val, INT8));
}

IOperand const * IOperand::createInt16(std::string const & value)
{
	int16_t	val = std::stoi(value);
	if (val <= -32767 || val >= +32767)
		throw OverflowError();
	return (new Operand<int16_t>(val, INT16));
}

IOperand const * IOperand::createInt32(std::string const & value)
{
	int32_t	val = std::stoi(value);
	return (new Operand<int32_t>(val, INT32));
}

IOperand const * IOperand::createFloat(std::string const & value)
{
	float	val = std::stof(value);
	return (new Operand<float>(val, FLOAT));
}

IOperand const * IOperand::createDouble(std::string const & value)
{
	double	val = std::stod(value);
	return (new Operand<double>(val, DOUBLE));
}

eOperandType operandTypeFromString(std::string &str)
{
	if ("int8" == str)
		return INT8;
	if ("int16" == str)
		return INT16;
	if ("int32" == str)
		return INT32;
	if ("float" == str)
		return FLOAT;
	if ("double" == str)
		return DOUBLE;
	return UNKNOW;
}

std::string operandTypeToString(eOperandType op)
{
	if (INT8 == op)
		return "int8";
	if (INT16 == op)
		return "int16";
	if (INT32 == op)
		return "int32";
	if (FLOAT == op)
		return "float";
	if (DOUBLE == op)
		return "double";
	return "UNKNOW";
}
