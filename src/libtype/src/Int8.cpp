#include "Int8.hpp"

/******************************************************************************/
/* Constructors                                                               */
/******************************************************************************/

Int8::Int8()
		:  IOperand()
{

}

Int8::Int8(Int8 const &model)
		:  IOperand(model)
{
	*this = model;
}

Int8::~Int8()
{

}

/******************************************************************************/
/* Getters Setters                                                            */
/******************************************************************************/

int getPrecision()
{
	 return (_type);
}

eOperandType getType()
{
	 return (_type);
}

/******************************************************************************/
/* Other Functions                                                            */
/******************************************************************************/

std::string	Int8::toString() const
{
	std::stringstream ss;
	ss << _val;
	return ss.str();
}

Int8& Int8::operator=(Int8 const &model)
{
	_val = model._val;
	_type = model._type;
	return *this;
}

std::ostream &operator<<(std::ostream &o, Int8 const &i)
{
	o << i.toString();
	return o;
}

Int8&	operator=(Int8 const &)
{

}

IOperand const * operator+( IOperand const & rhs )
{

}

IOperand const * operator-( IOperand const & rhs )
{

}

IOperand const * operator*( IOperand const & rhs )
{

}

IOperand const * operator/( IOperand const & rhs )
{

}

IOperand const * operator%( IOperand const & rhs )
{

}

