#include <assert.h>

#include "Operand.hpp"

int main()
{
	//test +
	IOperand const *a = IOperand::createOperand(INT8, "4");
	IOperand const *b = IOperand::createOperand(INT8, "5");
	// std::cout << (*a + *b)->toString() << " " << (*a + *b)->getType() << std::endl;
	assert(*(*a + *b) == *IOperand::createOperand(INT8, "9"));

	//test -
	assert(*(*a - *b) == *IOperand::createOperand(INT8, "-1"));

	//test *
	assert(*(*a * *b) == *IOperand::createOperand(INT8, "20"));

	//test /
	a = IOperand::createOperand(INT8, "20");
	b = IOperand::createOperand(INT8, "6");
	// std::cout << (*a / *b)->toString() << " " << (*a / *b)->getType() << std::endl;
	assert(*(*a / *b) == *IOperand::createOperand(INT8, "3"));

	//test %
	a = IOperand::createOperand(FLOAT, "4.4");
	b = IOperand::createOperand(FLOAT, "5.4");
	assert(*(*a % *b) == *IOperand::createOperand(INT32, "4"));
	return 0;
}
