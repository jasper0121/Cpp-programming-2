// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
	: myData()
{
}

// buffer constructor
string::string(const char* const ptr, const size_type count)
	: myData()
{
	myData.mySize = count; //mySize == �r�����
	if (count >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myData.myRes += (count / 16) * 16; //��X�@�ӭ���(count / 16)�A�N�䭼�H16��[�JmyRes(�bbuffer constructor�����X�i�W�h)
		myData.bx.ptr = new char[myData.myRes]; //�]count >= 16�A�G�t�m�ʺA�}�C
	}
	for (int n = 0; n < count; n++)
	{
		operator[](n) = ptr[n]; //�Nptr�����r���@�Ӥ@�ӽƻs�i��e�}�C��(�ھ�count���j�p�Aoperator[]�̪�myPtr()�i�ରbx.buf��bx.ptr)
	}
}

// fill constructor
string::string(const size_type count, const char ch)
	: myData()
{
	myData.mySize = count; //mySize == �r�����
	if (count >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myData.myRes += (count / 16) * 16; //��X�@�ӭ���(count / 16)�A�N�䭼�H16��[�JmyRes(�bfill constructor�����X�i�W�h)
		myData.bx.ptr = new char[myData.myRes]; //�]count >= 16�A�G�t�m�ʺA�}�C
	}
	for (int n = 0; n < count; n++)
	{
		operator[](n) = ch; //�Nch�@�Ӥ@�ӽƻs�i��e�}�C��
	}
}

// copy constructor
string::string(const string& right)
	: myData()
{
	myData.mySize = right.myData.mySize; //mySize == right�r�����
	if (right.myData.mySize >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myData.myRes += (right.myData.mySize / 16) * 16; //��X�@�ӭ���(right.mySize / 16)�A�N�䭼�H16��[�JmyRes(�bcopy constructor�����X�i�W�h)
		myData.bx.ptr = new char[myData.myRes + 1]; //�]right.mySize >= 16�A�G�t�m�ʺA�}�C�A��Ŷ� == myRes + 1�Ŧr��
	}
	for (int n = 0; n < right.myData.mySize + 1; n++) //�Nright[n]������(�]�A�Ŧr��)�ƻs�i��e�}�C��
	{
		operator[](n) = right[n];
	}
}

string::~string()
{
	if (myData.myRes > 15)
		delete[] myData.bx.ptr;
}

// assign (STL string)
string& string::operator=(const string& right)
{
	if (this != &right)
	{
		myData.mySize = right.myData.mySize; //mySize == right�r�����
		if (myData.myRes < right.myData.mySize) //�Y��e�}�C���`�Ŷ��� < right���r�����
		{
			if (myData.myRes != 15) //�Ybx.ptr�w���ʺA�}�C(�bmyRes == 15��bx.ptr�٥��t�m�ʺA�}�C)
			{
				delete[]myData.bx.ptr; //�h�����°}�C
			}
			myData.myRes = ((right.myData.mySize / 16) * 16 + 15 >= myData.myRes * 3 / 2) ? (right.myData.mySize / 16) * 16 + 15 : myData.myRes * 3 / 2; //myRes�bassign�����X�i�W�h
			myData.bx.ptr = new char[myData.myRes + 1]; //bx.ptr�t�m�ʺA�}�C�A��Ŷ� == myRes + 1�Ŧr��
		}
		for (int n = 0; n < right.myData.mySize + 1; n++) //�Nright[n]������(�]�A�Ŧr��)�ƻs�i��e�}�C��
		{
			operator[](n) = right[n];
		}
	}

	return *this;
}

// assign (C string)
string& string::operator=(const char* const ptr)
{
	int ptrSize = strlen(ptr); //strlen() == �r����סA��N�q�۷��size()
	myData.mySize = ptrSize; //mySize == ptr�r�����
	if (myData.myRes < ptrSize) //�Y��e�}�C���`�Ŷ��� < ptr���r�����
	{
		if (myData.myRes != 15) //�Ybx.ptr�w���ʺA�}�C(�bmyRes == 15��bx.ptr�٥��t�m�ʺA�}�C)
		{
			delete[]myData.bx.ptr; //�h�����°}�C
		}
		myData.myRes = ((ptrSize / 16) * 16 + 15 >= myData.myRes * 3 / 2) ? (ptrSize / 16) * 16 + 15 : myData.myRes * 3 / 2; //myRes�bassign�����X�i�W�h
		myData.bx.ptr = new char[myData.myRes + 1]; //bx.ptr�t�m�ʺA�}�C�A��Ŷ� == myRes + 1�Ŧr��
	}
	for (int n = 0; n < ptrSize + 1; n++) //�Nptr[n]������(�]�A�Ŧr��)�ƻs�i��e�}�C��
	{
		operator[](n) = ptr[n];
	}

	return *this;
}

// erase elements [off, off + count)
string& string::erase(size_t off, size_t count) //off == �}�C�W���s����m�Acount == ����(���ǤJ�ѼƮɹw�]��npos)
{
	if (off < myData.mySize)
	{
		if (count == npos || off + count > size()) //��erase�u��J1�ӰѼơA�ΧR�����Ϭq�W�Lsize()��
		{
			myData.mySize = off; //�h�NmySize�q��off(�۷�󦹰}�C��0 ~ off - 1���A�qoff�}�l�᭱���R)
		}
		else
		{
			for (int n = off + count; n < myData.mySize; n++) //n == �̫�Q�R�����U�@��
			{
				operator[](n - count) = operator[](n); //�N���᪺�ȥ������e��count��
			}
			myData.mySize -= count;
		}
	}

	return *this;
}

void string::clear()
{
	myData.mySize = 0;
	myData.myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return iterator(myData.myPtr());
}

string::const_iterator string::begin() const
{
	return const_iterator(myData.myPtr());
}

string::iterator string::end()
{
	return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::const_iterator string::end() const
{
	return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::reference string::operator[](size_type off)
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cout << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_reference string::operator[](size_type off) const
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cout << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_pointer string::data() const
{
	return myData.myPtr();
}

string::size_type string::size() const
{
	return myData.mySize;
}

// find
string::size_type string::find(char ch, size_type off) const //��r��ch�A�qoff����m(�w�]��0)�}�l�����
{
	for (int n = off; n < size(); n++) //�qoff�}�l
	{
		if (operator[](n) == ch) //�Y���ch
		{
			return n; //�h�^��n����m
		}
	}
	return npos; //�Y�䤣��h�^��npos
}

// substr (�^���r�ꤤ���@�q)
string string::substr(size_type off, size_type count) const //�qoff����m(�w�]��0)�}�l�����^���Acount == ����(�w�]��npos)
{
	string temp((count == npos || off + count > size()) ? size() - off : count, '\0'); //���M�w�n�l�r�ꪺsize
	for (int a = 0, b = off; a < temp.size(); a++, b++)
	{
		temp[a] = operator[](b); //�N���^���������ƻs��temp;
	}
	return temp;
}

// compare [ 0, size() ) with right for equality
bool string::equal(const string& right) const
{
	if (size() == right.size()) //�Y2�r�ꪺsize�ۦP
	{
		for (int n = 0; n < size(); n++) //�h�v���ˬd2�r��O�_�ۦP
		{
			if (operator[](n) != right[n])
			{
				return false;
			}
		}
		return true; //�వ�즹�N��2�r��ۦP
	}
	return false; //���즹�N��2�r��size()���P
}

bool operator==(const string& left, const string& right)
{
	return left.equal(right);
	//   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=(const string& left, const string& right)
{
	return !left.equal(right);
}

ostream& operator<<(ostream& ostr, string& str)
{
	for (size_t i = 0; i < str.size(); i++)
		ostr << str.data()[i];

	return ostr; // enables cout << x << y;
}