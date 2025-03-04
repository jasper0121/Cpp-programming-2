// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
	: integer(1)
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1)
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::assign(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		integer.assign(right.integer);

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal(const HugeInteger& right) const
{
	if (integer.size() != right.integer.size()) //若2者的size不相同，則2數必定不相等
	{
		return false;
	}
	else
	{
		for (int n = integer.size() - 1; n >= 0; n--) //若size相同，則逐格檢查2數是否相等
		{
			if (integer.begin()[n] != right.integer.begin()[n])
			{
				return false;
			}
			else if (n == 0) //能執行n == 0，代表確定2數相等
			{
				return true;
			}
		}
	}
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less(const HugeInteger& right) const //當前物件較小的話則回傳true
{
	if (integer.size() < right.integer.size()) //若當前的size < right的size
	{
		return true;
	}
	else if (integer.size() == right.integer.size()) //若size相同，則逐格檢查是否當前的數 < right的數
	{
		for (int n = integer.size() - 1; n >= 0; n--)
		{
			if (integer.begin()[n] < right.integer.begin()[n])
			{
				return true;
			}
			else if (integer.begin()[n] > right.integer.begin()[n] || n == 0) //能執行n == 0，代表當前的數 == right的數
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(const HugeInteger& right) const
{
	return (less(right) || equal(right));
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(HugeInteger& op2)
{
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	vector::iterator it1 = integer.begin();
	vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	vector::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.erase(sum.integer.end() - 1);

	return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract(HugeInteger& op2)
{
	HugeInteger zero;

	if (equal(op2))
		return zero;

	HugeInteger difference(*this);
	for (int n = 0; n < op2.integer.size(); n++) //2大數相減存回difference
	{
		difference.integer.begin()[n] -= op2.integer.begin()[n];
	}

	for (int n = 0; n < difference.integer.size() - 1; n++) //借位
	{
		if (difference.integer.begin()[n] < 0)
		{
			difference.integer.begin()[n + 1]--;
			difference.integer.begin()[n] += 10;
		}
	}

	while (difference.integer.begin()[difference.integer.size() - 1] == 0) //若最前面的數是0
	{
		difference.integer.erase(difference.integer.end() - 1); //則把0刪除
	}

	return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	unsigned int productSize = integer.size() + op2.integer.size();
	HugeInteger product(productSize);
	for (int b = 0; b < op2.integer.size(); b++) //b == 當前乘數正在運算的位數
	{
		for (int a = 0; a < integer.size(); a++) //a == 當前被乘數正在運算的位數
		{
			product.integer.begin()[a + b] += integer.begin()[a] * op2.integer.begin()[b]; //將當前的乘積依序加入
		}
	}

	for (int c = 0; c < productSize; c++) //進位
	{
		if (product.integer.begin()[c] > 9) //若該格的數 > 9
		{
			product.integer.begin()[c + 1] += product.integer.begin()[c] / 10; //算出進位次數，並把該值加入下一格
			product.integer.begin()[c] %= 10; //進位後，此格的值相當於除以10的餘數
		}
	}

	if (product.integer.begin()[productSize - 1] == 0) //若最前面的數是0
	{
		product.integer.erase(product.integer.end() - 1); //則把0刪除
	}

	return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide(HugeInteger& op2)
{
	HugeInteger zero;
	if (less(op2))
		return zero;

	HugeInteger remainder(*this); //將被除數複製給餘數
	HugeInteger buffer(integer.size()); //設buffer的空間數 == 被除數的空間數
	for (int a = buffer.integer.size() - 1, b = op2.integer.size() - 1; b >= 0; a--, b--) //將除數在陣列中做移位
	{
		buffer.integer.begin()[a] = op2.integer.begin()[b];
	}

	//若buffer <= remainder，則quotientSize == 被除數size - 除數size後再 + 1，反之則不需 + 1
	size_t quotientSize = (buffer.lessEqual(remainder)) ? integer.size() - op2.integer.size() + 1 : integer.size() - op2.integer.size();
	HugeInteger quotient(quotientSize);
	while (op2.lessEqual(remainder)) //若除數 <= 餘數
	{
		while (remainder.less(buffer)) //若餘數 < buffer
		{
			if (less(buffer) == false) //且若被除數 > buffer
			{
				quotientSize--; //若一開始運算的buffer > 被除數，則quotientSize不減
			}
			buffer.divideByTen(); //則buffer向右減少一位
		}
		remainder.assign(remainder.subtract(buffer)); //相減，並將其值存回餘數
		quotient.integer.begin()[quotientSize - 1]++; //商當前位數內的值 + 1
	}

	return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus(HugeInteger& op2)
{
	HugeInteger quotient = divide(op2);
	HugeInteger product = quotient.multiply(op2);
	HugeInteger remainder = subtract(product);
	return remainder;
}

// assign a vector of decimal digits into a HugeInteger
void HugeInteger::assign(const vector& v)
{
	integer.assign(v);
} // end function assign

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (vector::iterator it = integer.begin(); it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	vector::iterator it = integer.begin();
	vector::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.erase(integer.end() - 1);
}

// overloaded output operator
void HugeInteger::output(ostream& outFile)
{
	vector::iterator it = integer.end() - 1;
	for (; it != integer.begin() - 1; --it)
		if (*it < 10)
			outFile << *it;
	outFile << endl;
} // end function output