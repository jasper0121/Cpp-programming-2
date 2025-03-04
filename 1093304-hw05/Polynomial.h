#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Represents a term of a polynomial
struct Term
{
	bool operator!=(const Term& right) const
	{
		return coef != right.coef || expon != right.expon;
	}

	int coef;
	int expon;
};

// Polynomial class template definition
template< typename T >
class Polynomial
{
	// Overloaded stream insertion operator
	template< typename T >
	friend ostream& operator<<(ostream& output, Polynomial< T > a);
public:

	// Constructs an empty polynomial, with no terms.
	Polynomial(size_t n = 0)
		: polynomial(n)
	{
	}

	// Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
	Polynomial(const Polynomial& right)
		: polynomial(right.polynomial)
	{
	}

	// Destructor with empty body
	~Polynomial()
	{
	}

	// Copies all the terms from "right" into the polynomial
	const Polynomial< T > operator=(const Polynomial& right)
	{
		if (&right != this) // avoid self-assignment
			polynomial = right.polynomial;

		return *this; // enables x = y = z, for example
	}

	bool operator==(const Polynomial& right)
	{
		return polynomial == right.polynomial;
	}

	void setPolynomial(int coefficient[], int exponent[], int numTerms)
	{
		for (int i = 0; i < numTerms; i++)
		{
			polynomial[i].coef = coefficient[i];
			polynomial[i].expon = exponent[i];
		}
	}

	// addition assignment operator; Polynomial< T > += Polynomial< T >
	void operator+=(Polynomial& op2)
	{
		Polynomial< T > sum;
		int a = 0, b = 0; //a == �Q�[���Ab == �[��
		while (a < polynomial.size() && b < op2.polynomial.size()) //�Y2�h���������B�z��
		{
			if (polynomial[a].expon > op2.polynomial[b].expon) //�Y�Q�[����e������ > �[��
			{
				sum.attach(polynomial[a].coef, polynomial[a].expon); //�h�N�Q�[����e���Y�ƤΦ���[�Jsum
				a++;
			}
			else if (polynomial[a].expon < op2.polynomial[b].expon) //�Y�Q�[����e������ < �[��
			{
				sum.attach(op2.polynomial[b].coef, op2.polynomial[b].expon); //�h�N�[����e���Y�ƤΦ���[�Jsum
				b++;
			}
			else //�Y2����e������ۦP
			{
				if (polynomial[a].coef + op2.polynomial[b].coef != 0) //�B�Y2�Y�Ƭۥ[ != 0
				{
					sum.attach(polynomial[a].coef + op2.polynomial[b].coef, polynomial[a].expon); //�h�N2���ۥ[���Y�ƤγQ�[����e������[�Jsum
				}
				a++;
				b++;
			}
		}

		while (a < polynomial.size()) //�Y�Q�[���٥��Q�[��
		{
			sum.attach(polynomial[a].coef, polynomial[a].expon);
			a++;
		}

		while (b < op2.polynomial.size()) //�Y�[���٥��Q�[��
		{
			sum.attach(op2.polynomial[b].coef, op2.polynomial[b].expon);
			b++;
		}

		*this = sum;
	}

	// subtraction assignment operator; Polynomial< T > -= Polynomial< T >
	void operator-=(Polynomial& op2)
	{
		Polynomial< T > minus = -op2;
		*this += minus;
	}

	// multiplication operator; Polynomial< T > * Polynomial< T >
	Polynomial< T > operator*(Polynomial& op2)
	{
		Polynomial< T > product;
		Polynomial buffer(polynomial.size()); //�@���C�@���h�����ۭ��ɪ��Ȧs
		for (int b = 0; b < op2.polynomial.size(); b++) //b == ����
		{
			for (int a = 0; a < polynomial.size(); a++) //a == �Q����
			{
				buffer.polynomial[a].coef = polynomial[a].coef * op2.polynomial[b].coef;
				buffer.polynomial[a].expon = polynomial[a].expon + op2.polynomial[b].expon;
			}
			product += buffer; //�C���Nbuffer�����ȥ[�Jproduct
		}

		return product;
	}

	// modulus operator; Polynomial< T > / Polynomial< T > provided that the divisor is not equal to 0
	Polynomial< T > operator/(Polynomial& op2)
	{
		Polynomial quotient;
		Polynomial remainder(*this);
		Polynomial buffer;
		Polynomial monomial(1);
		while (remainder.degree() >= op2.degree() && remainder.polynomial.size() != 0) //�Y�l�����̰������ >= �����A�B�l�� != 0
		{
			monomial.polynomial[0].coef = remainder.polynomial[0].coef / op2.polynomial[0].coef; //��X�ðO����e�Ӫ��Y��
			monomial.polynomial[0].expon = remainder.polynomial[0].expon - op2.polynomial[0].expon; //��X�ðO����e�Ӫ�����
			quotient.attach(monomial.polynomial[0].coef, monomial.polynomial[0].expon); //�N��X���Y�ƻP����[�Jquotient��
			buffer = monomial * op2; //��X�ðO�����Qremainder��h����
			remainder -= buffer;
		}

		return quotient;
	}

	// modulus operator; Polynomial< T > % Polynomial< T > provided that the divisor is not equal to 0
	Polynomial< T > operator%(Polynomial& op2)
	{
		Polynomial quotient;
		Polynomial remainder(*this);
		Polynomial buffer;
		Polynomial monomial(1);

		while (remainder.degree() >= op2.degree() && remainder.polynomial.size() != 0) //�Y�l�����̰������ >= �����A�B�l�� != 0
		{
			monomial.polynomial[0].coef = remainder.polynomial[0].coef / op2.polynomial[0].coef; //��X�ðO����e�Ӫ��Y��
			monomial.polynomial[0].expon = remainder.polynomial[0].expon - op2.polynomial[0].expon; //��X�ðO����e�Ӫ�����
			buffer = monomial * op2; //��X�ðO�����Qremainder��h����
			remainder -= buffer;
		}

		return remainder;
	}

private:
	T polynomial; // a polynomial

	// Attaches a new term to the polynomial
	void attach(int coefficient, int exponent)
	{
		Term tempTerm;
		tempTerm.coef = coefficient;
		tempTerm.expon = exponent;
		polynomial.insert(polynomial.end(), tempTerm);
	}

	// Returns the minus of the current polynomial
	Polynomial< T > operator-()
	{
		Polynomial< T > minus(polynomial.size());
		typename T::iterator it2 = minus.polynomial.begin();
		typename T::iterator it1 = polynomial.begin();
		for (; it1 != polynomial.end(); ++it1, ++it2)
		{
			it2->coef = -it1->coef;
			it2->expon = it1->expon;
		}

		return minus;
	}

	// Returns true if and only if polynomial is a zero polynomial
	bool zero() const
	{
		return polynomial.empty();
	}

	// Returns the highest of degrees of polynomial's terms
	int degree() const
	{
		if (polynomial.empty())
			return 0;
		else
			return polynomial.begin()->expon;
	}

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T >
ostream& operator<<(ostream& output, Polynomial< T > a)
{
	if (a.zero())
	{
		output << 0 << endl;
		return output;
	}

	typename T::iterator it = a.polynomial.begin();

	if (it->coef < 0)
		cout << "-" << -it->coef;
	else if (it->coef > 0)
		cout << it->coef;

	if (it->expon > 0)
	{
		if (it->expon == 1)
			cout << "x";
		else
			cout << "x^" << it->expon;
	}

	for (++it; it != a.polynomial.end(); ++it)
	{
		if (it->coef < 0)
			cout << " - " << -it->coef;
		else if (it->coef > 0)
			cout << " + " << it->coef;

		if (it->expon > 0)
		{
			if (it->expon == 1)
				cout << "x";
			else
				cout << "x^" << it->expon;
		}
	}

	return output; // enables cout << x << y;
} // end function operator<<

#endif

