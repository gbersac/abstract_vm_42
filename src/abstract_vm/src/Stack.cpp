#include "Stack.hpp"

/******************************************************************************/
/* Constructors                                                               */
/******************************************************************************/

Stack::Stack()
{

}

Stack::Stack(Stack const &model)
{
	*this = model;
}

Stack::~Stack()
{

}

/******************************************************************************/
/* Getters Setters                                                            */
/******************************************************************************/

VecOper const & Stack::getList()const
{
	return _list;
}

/******************************************************************************/
/* Other Functions                                                            */
/******************************************************************************/

std::string	Stack::toString() const
{
	std::stringstream ss;
	ss << "Stack {" <<
			"}";
	return ss.str();
}

Stack& Stack::operator=(Stack const &model)
{
	_list = model._list;
	return *this;
}

std::ostream &operator<<(std::ostream &o, Stack const &i)
{
	o << i.toString();
	return o;
}

Oper Stack::pop()
{
	// TODO throw exception
	if (_list.size() == 0)
		throw EmptyStackError();
	Oper toReturn = _list.back();
	_list.pop_back();
	return (toReturn);
}

Oper Stack::last()
{
	// TODO throw exception
	if (_list.size() == 0)
		throw EmptyStackError();
	return (_list.back());
}

void Stack::push(Oper o)
{
	_list.push_back(o);
}
