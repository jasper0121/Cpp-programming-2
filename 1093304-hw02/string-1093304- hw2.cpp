#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
	: bx(),
	mySize(0),
	myRes(15)
{
}

// buffer constructor
string::string(const char* const ptr, const size_type count) //count���]�t�Ŧr��
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = count; //mySize == �r�����
	if (count >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myRes += (count / 16) * 16; //��X�@�ӭ���(count / 16)�A�N�䭼�H16��[�JmyRes(�bbuffer constructor�����X�i�W�h)
		bx.ptr = new char[myRes]; //�]count >= 16�A�G�t�m�ʺA�}�C
	}
	for (int n = 0; n < count; n++)
	{
		element(n) = ptr[n]; //�Nptr�����r���@�Ӥ@�ӽƻs�i��e�}�C��(�ھ�count���j�p�Aelement�̪�myPtr()�i�ରbx.buf��bx.ptr)
	}
}

// fill constructor
string::string(const size_type count, const char ch) //count���]�t�Ŧr��
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = count; //mySize == �r�����
	if (count >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myRes += (count / 16) * 16; //��X�@�ӭ���(count / 16)�A�N�䭼�H16��[�JmyRes(�bfill constructor�����X�i�W�h)
		bx.ptr = new char[myRes]; //�]count >= 16�A�G�t�m�ʺA�}�C
	}
	for (int n = 0; n < count; n++)
	{
		element(n) = ch; //�Nch�@�Ӥ@�ӽƻs�i��e�}�C��
	}
}

// copy constructor
string::string(const string& right)
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = right.mySize; //mySize == right�r�����
	if (right.mySize >= 16) //�Y�Ƕi�Ӫ��r����� >= 16
	{
		myRes += (right.mySize / 16) * 16; //��X�@�ӭ���(right.mySize / 16)�A�N�䭼�H16��[�JmyRes(�bcopy constructor�����X�i�W�h)
		bx.ptr = new char[myRes + 1]; //�]right.mySize >= 16�A�G�t�m�ʺA�}�C�A��Ŷ� == myRes + 1�Ŧr��
	}
	for (int n = 0; n < right.mySize + 1; n++) //�Nright.element(n)������(�]�A�Ŧr��)�ƻs�i��e�}�C��
	{
		element(n) = right.element(n);
	}
}

string::~string()
{
	if (myRes > 15)
		delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

const string::value_type* string::myPtr() const
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

string& string::assign(const string& right)
{
	mySize = right.mySize; //mySize == right�r�����
	if (myRes < right.mySize) //�Y��e�}�C���`�Ŷ��� < right���r�����
	{
		if (myRes != 15) //�Ybx.ptr�w���ʺA�}�C(�bmyRes == 15��bx.ptr�٥��t�m�ʺA�}�C)
		{
			delete[]bx.ptr; //�h�����°}�C
		}
		myRes = ((right.mySize / 16) * 16 + 15 >= myRes * 3 / 2) ? (right.mySize / 16) * 16 + 15 : myRes * 3 / 2; //myRes�bassign�����X�i�W�h
		bx.ptr = new char[myRes + 1]; //bx.ptr�t�m�ʺA�}�C�A��Ŷ� == myRes + 1�Ŧr��
	}
	for (int n = 0; n < right.mySize + 1; n++) //�Nright.element(n)������(�]�A�Ŧr��)�ƻs�i��e�}�C��
	{
		element(n) = right.element(n);
	}
	return *this;
}

string::iterator string::insert(const_iterator where, const char ch)
{
	if (where >= myPtr() && where <= myPtr() + mySize)
	{
		if (mySize + 1 <= myRes) //�Y�٦��Ŷ��i�H��J�s����
		{
			for (int a = mySize; a >= 0; a--)
			{
				if (myPtr() + a == where) //�YmyPtr()�}�C�W�Y��m == ���w���J���a�}
				{
					element(a) = ch; //�N�s�����[�J�Ӯ�}�C
					break; //���J�����A���X�j��
				}
				element(a) = element(a - 1); //�q�̫�@�Ӥ����}�l�A�C���N�Ӥ������Ჾ1��
			}
		}
		else if (mySize == myRes)
		{
			int tempRes = (myRes < 32) ? myRes + 16 : myRes * 3 / 2; //�ŧi�ȦsRes�A��Ȯھڷ�emyRes���Ȧөw(myRes�binsert�����X�i�W�h)
			pointer temp = new char[tempRes + 1]; //�ŧi�Ȧs�ʺA�}�C�A��Ŷ� == tempRes + 1�Ŧr��
			for (int a = 0, b = 0; a < mySize + 1; a++, b++)
			{
				if (myPtr() + a == where) //�YmyPtr()�}�C�W�Y��m == ���w���J���a�}
				{
					temp[a] = ch; //�N�s�����[�J�Ӯ�}�C
					b--; //����element(b)���ȥ��ƻs�A�Yb����1�h�ӭȤ��|�Q�s�Jtemp[a]��
					continue;
				}
				temp[a] = element(b); //�Nelement(b)�ƻs��temp
			}
			if (myRes != 15) //�Ybx.ptr�w���ʺA�}�C(�bmyRes == 15��bx.ptr�٥��t�m�ʺA�}�C)
			{
				delete[]bx.ptr; //�h�����°}�C
			}
			bx.ptr = temp; //�Ntemp���a�}��bx.ptr(�ϱobx.ptr���Vtemp���}�C)
			myRes = tempRes; //��smyRes����
		}
		mySize++; //�]���J1�����A�GmySize + 1
		element(mySize) = '\0'; //�b�r�굲����J�Ŧr��(���Y����]���|��)
	}
	else
		return iterator(nullptr);
}

string::iterator string::erase(const_iterator where)
{
	if (where >= myPtr() && where < myPtr() + mySize)
	{
		for (int i = (where - myPtr()) + 1; i < mySize; i++) //(where - myPtr()) == �}�C�W���R������m�Ai == �q�Ӧ�m���U�@��}�l
		{
			element(i - 1) = element(i); //�N���᪺�ȥ������e��1��
		}
		mySize--; //�]�R��1�����A�GmySize - 1
	}
	else
		return iterator(nullptr);
}

void string::clear()
{
	mySize = 0;
	myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return myPtr();
}

string::const_iterator string::begin() const
{
	return const_iterator(myPtr());
}

string::iterator string::end()
{
	return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
	return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::element(const size_type off)
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::const_reference string::element(const size_type off) const
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::reference string::front()
{
	return myPtr()[0];
}

string::const_reference string::front() const
{
	return myPtr()[0];
}

string::reference string::back()
{
	return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
	return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
	return myPtr();
}

string::size_type string::size() const
{
	return mySize;
}

string::size_type string::capacity() const
{
	return myRes;
}

bool string::empty() const
{
	return mySize == 0;
}