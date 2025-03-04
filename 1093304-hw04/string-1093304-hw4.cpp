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
	myData.mySize = count; //mySize == 字串長度
	if (count >= 16) //若傳進來的字串長度 >= 16
	{
		myData.myRes += (count / 16) * 16; //算出一個倍數(count / 16)，將其乘以16後加入myRes(在buffer constructor內的擴展規則)
		myData.bx.ptr = new char[myData.myRes]; //因count >= 16，故配置動態陣列
	}
	for (int n = 0; n < count; n++)
	{
		operator[](n) = ptr[n]; //將ptr內的字元一個一個複製進當前陣列內(根據count的大小，operator[]裡的myPtr()可能為bx.buf或bx.ptr)
	}
}

// fill constructor
string::string(const size_type count, const char ch)
	: myData()
{
	myData.mySize = count; //mySize == 字串長度
	if (count >= 16) //若傳進來的字串長度 >= 16
	{
		myData.myRes += (count / 16) * 16; //算出一個倍數(count / 16)，將其乘以16後加入myRes(在fill constructor內的擴展規則)
		myData.bx.ptr = new char[myData.myRes]; //因count >= 16，故配置動態陣列
	}
	for (int n = 0; n < count; n++)
	{
		operator[](n) = ch; //將ch一個一個複製進當前陣列內
	}
}

// copy constructor
string::string(const string& right)
	: myData()
{
	myData.mySize = right.myData.mySize; //mySize == right字串長度
	if (right.myData.mySize >= 16) //若傳進來的字串長度 >= 16
	{
		myData.myRes += (right.myData.mySize / 16) * 16; //算出一個倍數(right.mySize / 16)，將其乘以16後加入myRes(在copy constructor內的擴展規則)
		myData.bx.ptr = new char[myData.myRes + 1]; //因right.mySize >= 16，故配置動態陣列，其空間 == myRes + 1空字元
	}
	for (int n = 0; n < right.myData.mySize + 1; n++) //將right[n]內的值(包括空字元)複製進當前陣列內
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
		myData.mySize = right.myData.mySize; //mySize == right字串長度
		if (myData.myRes < right.myData.mySize) //若當前陣列的總空間數 < right的字串長度
		{
			if (myData.myRes != 15) //若bx.ptr已有動態陣列(在myRes == 15時bx.ptr還未配置動態陣列)
			{
				delete[]myData.bx.ptr; //則釋放舊陣列
			}
			myData.myRes = ((right.myData.mySize / 16) * 16 + 15 >= myData.myRes * 3 / 2) ? (right.myData.mySize / 16) * 16 + 15 : myData.myRes * 3 / 2; //myRes在assign內的擴展規則
			myData.bx.ptr = new char[myData.myRes + 1]; //bx.ptr配置動態陣列，其空間 == myRes + 1空字元
		}
		for (int n = 0; n < right.myData.mySize + 1; n++) //將right[n]內的值(包括空字元)複製進當前陣列內
		{
			operator[](n) = right[n];
		}
	}

	return *this;
}

// assign (C string)
string& string::operator=(const char* const ptr)
{
	int ptrSize = strlen(ptr); //strlen() == 字串長度，其意義相當於size()
	myData.mySize = ptrSize; //mySize == ptr字串長度
	if (myData.myRes < ptrSize) //若當前陣列的總空間數 < ptr的字串長度
	{
		if (myData.myRes != 15) //若bx.ptr已有動態陣列(在myRes == 15時bx.ptr還未配置動態陣列)
		{
			delete[]myData.bx.ptr; //則釋放舊陣列
		}
		myData.myRes = ((ptrSize / 16) * 16 + 15 >= myData.myRes * 3 / 2) ? (ptrSize / 16) * 16 + 15 : myData.myRes * 3 / 2; //myRes在assign內的擴展規則
		myData.bx.ptr = new char[myData.myRes + 1]; //bx.ptr配置動態陣列，其空間 == myRes + 1空字元
	}
	for (int n = 0; n < ptrSize + 1; n++) //將ptr[n]內的值(包括空字元)複製進當前陣列內
	{
		operator[](n) = ptr[n];
	}

	return *this;
}

// erase elements [off, off + count)
string& string::erase(size_t off, size_t count) //off == 陣列上的編號位置，count == 長度(未傳入參數時預設為npos)
{
	if (off < myData.mySize)
	{
		if (count == npos || off + count > size()) //當erase只放入1個參數，或刪除的區段超過size()時
		{
			myData.mySize = off; //則將mySize訂為off(相當於此陣列有0 ~ off - 1號，從off開始後面全刪)
		}
		else
		{
			for (int n = off + count; n < myData.mySize; n++) //n == 最後被刪除的下一格
			{
				operator[](n - count) = operator[](n); //將之後的值全部往前移count格
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
string::size_type string::find(char ch, size_type off) const //找字元ch，從off號位置(預設為0)開始往後找
{
	for (int n = off; n < size(); n++) //從off開始
	{
		if (operator[](n) == ch) //若找到ch
		{
			return n; //則回傳n號位置
		}
	}
	return npos; //若找不到則回傳npos
}

// substr (擷取字串中的一段)
string string::substr(size_type off, size_type count) const //從off號位置(預設為0)開始往後擷取，count == 長度(預設為npos)
{
	string temp((count == npos || off + count > size()) ? size() - off : count, '\0'); //先決定好子字串的size
	for (int a = 0, b = off; a < temp.size(); a++, b++)
	{
		temp[a] = operator[](b); //將欲擷取的部分複製給temp;
	}
	return temp;
}

// compare [ 0, size() ) with right for equality
bool string::equal(const string& right) const
{
	if (size() == right.size()) //若2字串的size相同
	{
		for (int n = 0; n < size(); n++) //則逐格檢查2字串是否相同
		{
			if (operator[](n) != right[n])
			{
				return false;
			}
		}
		return true; //能做到此代表2字串相同
	}
	return false; //做到此代表2字串size()不同
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