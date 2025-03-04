// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "vector-1093304-hw7-1.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger);
public:
	HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger& operator=(const HugeInteger& right); // assignment operator

	// assign right to integer, i.e., integer = right
	void operator=(T& right);

	bool operator==(HugeInteger& right); // less than or equal to

	bool operator<(HugeInteger& right);  // less than

	bool operator<=(HugeInteger& right); // less than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger& op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger& op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger& op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger& op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger& op2);

	HugeInteger& operator++(); // prefix increment operator

	HugeInteger operator++(int); // postfix increment operator

	HugeInteger& operator--(); // prefix decrement operator

	HugeInteger operator--(int); // postfix decrement operator

	bool isZero();           // return true if and only if all digits are zero
private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

template< typename T >
void HugeInteger< T >::operator=(T& right)
{
	integer = right;
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{
	if (integer.size() == right.integer.size()) //璝2计size
	{
		typename T::iterator thisPtr = integer.end() - 1; //thisPtr讽玡程蔼
		typename T::iterator rightPtr = right.integer.end() - 1; //rightPtrright程蔼
		for (; thisPtr != integer.begin() - 1; thisPtr--, rightPtr--) //2Ptr–Ω┕1
		{
			if (*thisPtr < *rightPtr)
			{
				return true;
			}
			else if (*thisPtr > *rightPtr)
			{
				return false;
			}
		}
		return false; //暗2计单
	}

	return (integer.size() < right.integer.size()); //璝讽玡size < rightsize玥肚true玥肚false
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger& op2)
{
	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	typename T::iterator it1 = integer.begin();
	typename T::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	typename T::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9)
		{
			*it3 -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.erase(sum.integer.end() - 1);

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger& op2)
{
	HugeInteger zero;

	if (*this == op2)
		return zero;

	HugeInteger difference(*this);
	typename T::iterator differPtr = difference.integer.begin(); //differPtrdifference程
	typename T::iterator op2Ptr = op2.integer.begin(); //op2Ptrop2程
	for (; op2Ptr != op2.integer.end(); differPtr++, op2Ptr++)
	{
		if (*differPtr < *op2Ptr) //璝difference讽玡计 < op2讽玡计
		{
			*differPtr += 10; //玥difference讽玡计 + 10絋玂unsigned int
			typename T::iterator borrow = differPtr; //ミborrow眖differPtrヘ玡┮竚秨﹍
			while (borrow++, *borrow == 0) //–Ω盢borrow┕オ耞璝赣 == 0
			{
				*borrow = 9; //玥赣计惠砆珿盢赣э9
			}
			(*borrow)--; //琘计 != 0珿赣计 - 1(璝ぃ珹腹玥borrow穦)
		}
		*differPtr -= *op2Ptr; //difference讽玡计 -= op2讽玡计
	}

	while (difference.integer.back() == 0) //璝程蔼计 == 0玥erase
	{
		difference.integer.erase(difference.integer.end() - 1);
	}

	return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	HugeInteger product(integer.size() + op2.integer.size());
	for (typename T::iterator op2Ptr = op2.integer.begin(), proPtr = product.integer.begin(); op2Ptr != op2.integer.end(); op2Ptr++, proPtr++)
	{
		//–ΩthisPtr讽玡程pro_current眖proPtrヘ玡┮竚秨﹍羆–Ω
		for (typename T::iterator thisPtr = integer.begin(), pro_current = proPtr; thisPtr != integer.end(); thisPtr++, pro_current++)
		{
			*pro_current += (*op2Ptr) * (*thisPtr);
		}
	}

	for (typename T::iterator proPtr = product.integer.begin(); proPtr != product.integer.end(); proPtr++) //秈
	{
		if (*proPtr >= 10)
		{
			*(proPtr + 1) += *proPtr / 10;
			*proPtr %= 10;
		}
	}

	if (product.integer.back() == 0) //璝程玡 == 0
	{
		product.integer.erase(product.integer.end() - 1); //玥盢程玡0埃
	}

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger remainder(*this); //盢砆埃计狡籹倒緇计
	HugeInteger buffer(integer.size()); //砞buffer丁计 == 砆埃计丁计
	size_t quotientSize = integer.size() - op2.integer.size(); //quotientSize == 砆埃计size - 埃计size
	for (typename T::iterator buffPtr = buffer.integer.end() - 1, op2Ptr = op2.integer.end() - 1; op2Ptr != op2.integer.begin() - 1; buffPtr--, op2Ptr--)
	{
		*buffPtr = *op2Ptr; //埃计簿
	}

	if (remainder < buffer) //璝砆埃计(remainder) < buffer
	{
		buffer.divideByTen(); //玥buffer搭ぶ
	}
	else
	{
		quotientSize++; //玥quotientSize + 1
	}

	HugeInteger quotient(quotientSize);
	for (typename T::iterator quoPtr = quotient.integer.end() - 1; op2 <= remainder;) //quoPtrquotient程蔼璝埃计 <= 緇计
	{
		remainder = remainder - buffer; //搭盢ㄤ緇计
		(*quoPtr)++; //坝讽玡计ず + 1
		while (remainder < buffer) //璝緇计 < buffer
		{
			buffer.divideByTen(); //玥buffer搭ぶ
			quoPtr--; //quoPtr┕
		}
	}

	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger product = quotient * op2;
	HugeInteger remainder = (*this) - product;
	return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
	helpIncrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpIncrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpDecrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	typename T::iterator it = integer.begin();
	for (; it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it = integer.begin() + 1;
	for (; it != integer.end(); ++it)
		*(it - 1) = *it;
	integer.erase(integer.end() - 1);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename T::iterator it = integer.begin();
	(*it)++;
	typename T::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		if (*it == 10)
		{
			*it = 0;
			(*it2)++;
		}

	if ((*it) == 10)
	{
		*it = 0;
		integer.insert(integer.end(), 1);
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; *it == 0; ++it)
		*it = 9;

	(*it)--;

	if (!isZero() && integer.back() == 0)
		integer.erase(integer.end() - 1);
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	typename T::iterator it = hugeInteger.integer.end() - 1;
	for (; it != hugeInteger.integer.begin() - 1; --it)
		if (*it < 10)
			output << *it;

	return output; // enables cout << x << y;
}

#endif