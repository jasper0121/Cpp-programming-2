// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "vector-1093304-hw9.h"
#include "list-1093304-hw9.h"
#include "deque-1093304-hw9.h"

/*
#include <vector>
#include <list>
#include <deque>
using std::vector;
using std::list;
using std::deque;
*/

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger);
public:
	HugeInteger(size_t n = 0); // constructor; construct a zero HugeInteger with mySize n

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

	bool isZero(); // return true if and only if all digits are zero

private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger(size_t n)
	: integer((n > 0) ? n : 1)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T >& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger< T >& right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
} // end function operator=

template< typename T >
void HugeInteger< T >::operator=(T& right)
{
	integer = right;
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger< T >& right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger< T >& right)
{
	if (integer.size() == right.integer.size()) //若2數的size相同
	{
		typename T::iterator thisPtr = --integer.end(); //thisPtr指向當前的最高位(--integer.end()建立並回傳1個iterator後再向右指，故不影響內部的myLast)
		typename T::iterator rightPtr = --right.integer.end(); //rightPtr指向right的最高位
		for (; thisPtr != --integer.begin(); thisPtr--, rightPtr--) //--integer.begin() == 1個iterator先指向begin的右邊後才做判斷，2Ptr每次往右指
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
		return false; //做到此代表2數相等
	}

	return (integer.size() < right.integer.size()); //若當前的size < right的size則回傳true，否則回傳false
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T >& right)
{
	return (*this == right || *this < right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger< T >& op2)
{
	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);
	typename T::iterator it1 = integer.begin();
	typename T::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	typename T::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	typename T::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*it4)++;
		}

	if (*it3 == 0)
		sum.integer.erase(--(sum.integer.end()));

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T >& op2)
{
	HugeInteger< T > zero;

	if (*this == op2)
		return zero;

	HugeInteger< T > difference(*this);
	typename T::iterator differPtr = difference.integer.begin(); //differPtr指向difference的最低位
	typename T::iterator op2Ptr = op2.integer.begin(); //op2Ptr指向op2的最低位
	for (; op2Ptr != op2.integer.end(); differPtr++, op2Ptr++)
	{
		if (*differPtr < *op2Ptr) //若difference當前位數的值 < op2當前位數的值
		{
			*differPtr += 10; //則difference當前位數的值先 + 10以確保unsigned int
			typename T::iterator borrow = differPtr; //建立借位borrow，從differPtr目前所指的位置開始
			while (borrow++, *borrow == 0) //每次先將borrow往左指，再判斷若該值 == 0
			{
				*borrow = 9; //則代表該位數的值也需被借位，故將該值改為9
			}
			(*borrow)--; //直到某位數的值 != 0，代表可借位，故該位數的值 - 1(若不括號則borrow會先向右指後再取子)
		}
		*differPtr -= *op2Ptr; //difference當前位數的值 -= op2當前位數的值
	}

	while (difference.integer.back() == 0) //若最高位數的值 == 0，則erase
	{
		difference.integer.erase(--difference.integer.cend()); //因difference非const，故會使用非const的end()，但erase的傳入值需為const，故只能使用cend()
	}

	return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T >& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t productSize = op1Size + op2Size;

	HugeInteger< T > product(productSize);
	for (typename T::iterator op2Ptr = op2.integer.begin(), proPtr = product.integer.begin(); op2Ptr != op2.integer.end(); op2Ptr++, proPtr++)
	{
		//每次thisPtr指向當前的最低位，pro_current從proPtr目前所指的位置開始加總每次相乘的值
		for (typename T::iterator thisPtr = integer.begin(), pro_current = proPtr; thisPtr != integer.end(); thisPtr++, pro_current++)
		{
			*pro_current += (*op2Ptr) * (*thisPtr);
		}
	}

	for (typename T::iterator proPtr = product.integer.begin(); proPtr != product.integer.end();) //進位
	{
		if (*proPtr >= 10) //若當前位數的值 >= 10
		{
			int temp = *proPtr / 10; //先將應進位的數存起來
			*proPtr %= 10;
			*(++proPtr) += temp; //再將temp加到下一位數中
		}
		else
		{
			proPtr++; //否則proPtr直接指向下一位數
		}
	}

	if (product.integer.back() == 0) //若最前面的值 == 0
	{
		product.integer.erase(--product.integer.cend()); //則將最前面的0刪除
	}

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T >& op2)
{
	HugeInteger< T > zero;
	if (*this < op2)
		return zero;

	HugeInteger remainder(*this); //將被除數複製給餘數
	HugeInteger buffer(integer.size()); //設buffer的空間數 == 被除數的空間數
	size_t quotientSize = integer.size() - op2.integer.size(); //quotientSize == 被除數size - 除數size
	for (typename T::iterator buffPtr = --buffer.integer.end(), op2Ptr = --op2.integer.end(); op2Ptr != --op2.integer.begin(); buffPtr--, op2Ptr--)
	{
		*buffPtr = *op2Ptr; //除數移位
	}

	if (remainder < buffer) //若被除數(remainder) < buffer
	{
		buffer.divideByTen(); //則buffer向右減少一位
	}
	else
	{
		quotientSize++; //否則quotientSize + 1
	}

	HugeInteger quotient(quotientSize);
	for (typename T::iterator quoPtr = --quotient.integer.end(); op2 <= remainder;) //quoPtr指向quotient的最高位，若除數 <= 餘數
	{
		remainder = remainder - buffer; //相減，並將其值存回餘數
		(*quoPtr)++; //商當前位數內的值 + 1
		while (remainder < buffer) //若餘數 < buffer
		{
			buffer.divideByTen(); //則buffer向右減少一位
			quoPtr--; //quoPtr往下一位指
		}
	}

	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T >& op2)
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
	HugeInteger< T > temp = *this; // hold current state of object
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

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;

	integer.erase(--integer.end());
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename T::iterator it = integer.begin();
	if (isZero())
		(*it)++;
	else
	{
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
		integer.erase(--(integer.end()));
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	if (hugeInteger.isZero())
		output << 0;
	else
	{
		typename T::reverse_iterator it = hugeInteger.integer.rbegin();
		for (; it != hugeInteger.integer.rend(); ++it)
			if (*it < 10)
				output << *it;
	}

	return output; // enables cout << x << y;
}