#ifndef IOPERAND_H
# define IOPERAND_H

# include <string>
# include <iostream>

/**
 * Type of the operand. Tydef are ordered by order of precision
 * (least precise first).
 */
typedef enum	OperandType
{
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE
}				eOperandType;

class IOperand {
public:
	virtual int					getPrecision(void) const = 0;
	virtual eOperandType		getType(void) const = 0;
	static IOperand const *		createOperand(eOperandType type, std::string const & value);

	virtual IOperand const *	operator+(IOperand const & rhs) const = 0;
	virtual IOperand const *	operator-(IOperand const & rhs) const = 0;
	virtual IOperand const *	operator*(IOperand const & rhs) const = 0;
	virtual IOperand const *	operator/(IOperand const & rhs) const = 0;
	virtual IOperand const *	operator%(IOperand const & rhs) const = 0;
	virtual bool				operator==(IOperand const & rhs) const = 0;

	virtual std::string const &	toString(void) const = 0;
	virtual ~IOperand(void) {}

private:
	static IOperand const * createInt8(std::string const & value);
	static IOperand const * createInt16(std::string const & value);
	static IOperand const * createInt32(std::string const & value);
	static IOperand const * createFloat(std::string const & value);
	static IOperand const * createDouble(std::string const & value);
};

template <typename T>
class Operand : public IOperand
{
public:
	Operand();
	Operand(T value, eOperandType type);
	Operand(Operand const &);
	virtual ~Operand();
	int getPrecision(void) const;
	eOperandType getType(void) const;

	Operand&			operator=(Operand const &);
	IOperand const *	operator+(IOperand const & rhs) const;
	IOperand const *	operator-(IOperand const & rhs) const;
	IOperand const *	operator*(IOperand const & rhs) const;
	IOperand const *	operator/(IOperand const & rhs) const;
	IOperand const *	operator%(IOperand const & rhs) const;
	bool				operator==(IOperand const & rhs) const;

	std::string const &	toString(void) const;

private:
	/**
	 * Return the most precise type between this instance of operand and
	 * another.
	 */
	eOperandType	mostPreciseType(IOperand const & rhs) const;

	eOperandType	type;
	T				value;
	std::string		str;
};

template <typename T>
Operand<T>::Operand()
		: value(0), type(INT32), str("0")
{

}

template <typename T>
Operand<T>::Operand(T value, eOperandType type)
		: type(type), value(value), str(std::to_string(value))
{
}

template <typename T>
Operand<T>::Operand(Operand const &model)
{
	*this = model;
}

template <typename T>
Operand<T>::~Operand()
{

}

template <typename T>
std::string const &	Operand<T>::toString() const
{
	return this->str;
}

template <typename T>
Operand<T>&			Operand<T>::operator=(Operand const &)
{
	return *this;
}

template <typename T>
std::ostream &		operator<<(std::ostream &o, Operand<T> const &i)
{
	o << i.toString();
	return o;
}

template <typename T>
IOperand const * 	Operand<T>::operator+(IOperand const & rhs) const
{
	eOperandType newType = mostPreciseType(rhs);
	double rvalue = std::stod(rhs.toString());
	return (new Operand(rvalue + this->value, newType));
}

template <typename T>
IOperand const * 	Operand<T>::operator-( IOperand const & rhs) const
{
	eOperandType newType = mostPreciseType(rhs);
	double rvalue = std::stod(rhs.toString());
	return (new Operand(this->value - rvalue, newType));
}

template <typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) const
{
	eOperandType newType = mostPreciseType(rhs);
	double rvalue = std::stod(rhs.toString());
	return (new Operand(rvalue * this->value, newType));
}

template <typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) const
{
	eOperandType newType = mostPreciseType(rhs);
	double rvalue = std::stod(rhs.toString());
	return (new Operand(this->value / rvalue, newType));
}

template <typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) const
{
	eOperandType newType = mostPreciseType(rhs);
	if (newType == DOUBLE || newType == FLOAT)
		newType = INT32;
	int lvalue = static_cast<int>(this->value);
	int rvalue = std::stoi(rhs.toString());
	return (new Operand(lvalue % rvalue, newType));
}

template <typename T>
bool				Operand<T>::operator==(IOperand const & rhs) const
{
	// if (!this->type == rhs.type)
	// 	return (false);
	return (this->value == std::stod(rhs.toString()));
}

template <typename T>
int					Operand<T>::getPrecision(void) const
{
	return (this->type);
}

template <typename T>
eOperandType		Operand<T>::getType(void) const
{
	return (this->type);
}

template <typename T>
eOperandType		Operand<T>::mostPreciseType(IOperand const & rhs) const
{
	if (this->type > rhs.getType())
		return (this->type);
	return (rhs.getType());
}

#endif /*IOPERAND_H*/
