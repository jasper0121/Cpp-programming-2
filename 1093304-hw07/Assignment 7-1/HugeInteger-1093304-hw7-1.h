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
	if (integer.size() == right.integer.size()) //�Y2�ƪ�size�ۦP
	{
		typename T::iterator thisPtr = integer.end() - 1; //thisPtr���V��e���̰���
		typename T::iterator rightPtr = right.integer.end() - 1; //rightPtr���Vright���̰���
		for (; thisPtr != integer.begin() - 1; thisPtr--, rightPtr--) //2Ptr�C�����k��1��
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
		return false; //���즹�N��2�Ƭ۵�
	}

	return (integer.size() < right.integer.size()); //�Y��e��size < right��size�h�^��true�A�_�h�^��false
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
	typename T::iterator differPtr = difference.integer.begin(); //differPtr���Vdifference���̧C��
	typename T::iterator op2Ptr = op2.integer.begin(); //op2Ptr���Vop2���̧C��
	for (; op2Ptr != op2.integer.end(); differPtr++, op2Ptr++)
	{
		if (*differPtr < *op2Ptr) //�Ydifference��e��ƪ��� < op2��e��ƪ���
		{
			*differPtr += 10; //�hdifference��e��ƪ��ȥ� + 10�H�T�Ounsigned int
			typename T::iterator borrow = differPtr; //�إ߭ɦ�borrow�A�qdifferPtr�ثe�ҫ�����m�}�l
			while (borrow++, *borrow == 0) //�C�����Nborrow�������A�A�P�_�Y�ӭ� == 0
			{
				*borrow = 9; //�h�N��Ӧ�ƪ��Ȥ]�ݳQ�ɦ�A�G�N�ӭȧאּ9
			}
			(*borrow)--; //����Y��ƪ��� != 0�A�N��i�ɦ�A�G�Ӧ�ƪ��� - 1(�Y���A���hborrow�|���V�k����A���l)
		}
		*differPtr -= *op2Ptr; //difference��e��ƪ��� -= op2��e��ƪ���
	}

	while (difference.integer.back() == 0) //�Y�̰���ƪ��� == 0�A�herase
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
		//�C��thisPtr���V��e���̧C��Apro_current�qproPtr�ثe�ҫ�����m�}�l�[�`�C���ۭ�����
		for (typename T::iterator thisPtr = integer.begin(), pro_current = proPtr; thisPtr != integer.end(); thisPtr++, pro_current++)
		{
			*pro_current += (*op2Ptr) * (*thisPtr);
		}
	}

	for (typename T::iterator proPtr = product.integer.begin(); proPtr != product.integer.end(); proPtr++) //�i��
	{
		if (*proPtr >= 10)
		{
			*(proPtr + 1) += *proPtr / 10;
			*proPtr %= 10;
		}
	}

	if (product.integer.back() == 0) //�Y�̫e������ == 0
	{
		product.integer.erase(product.integer.end() - 1); //�h�N�̫e����0�R��
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

	HugeInteger remainder(*this); //�N�Q���ƽƻs���l��
	HugeInteger buffer(integer.size()); //�]buffer���Ŷ��� == �Q���ƪ��Ŷ���
	size_t quotientSize = integer.size() - op2.integer.size(); //quotientSize == �Q����size - ����size
	for (typename T::iterator buffPtr = buffer.integer.end() - 1, op2Ptr = op2.integer.end() - 1; op2Ptr != op2.integer.begin() - 1; buffPtr--, op2Ptr--)
	{
		*buffPtr = *op2Ptr; //���Ʋ���
	}

	if (remainder < buffer) //�Y�Q����(remainder) < buffer
	{
		buffer.divideByTen(); //�hbuffer�V�k��֤@��
	}
	else
	{
		quotientSize++; //�_�hquotientSize + 1
	}

	HugeInteger quotient(quotientSize);
	for (typename T::iterator quoPtr = quotient.integer.end() - 1; op2 <= remainder;) //quoPtr���Vquotient���̰���A�Y���� <= �l��
	{
		remainder = remainder - buffer; //�۴�A�ñN��Ȧs�^�l��
		(*quoPtr)++; //�ӷ�e��Ƥ����� + 1
		while (remainder < buffer) //�Y�l�� < buffer
		{
			buffer.divideByTen(); //�hbuffer�V�k��֤@��
			quoPtr--; //quoPtr���U�@���
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