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
string::string(const char* const ptr, const size_type count) //count不包含空字元
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = count; //mySize == 字串長度
	if (count >= 16) //若傳進來的字串長度 >= 16
	{
		myRes += (count / 16) * 16; //算出一個倍數(count / 16)，將其乘以16後加入myRes(在buffer constructor內的擴展規則)
		bx.ptr = new char[myRes]; //因count >= 16，故配置動態陣列
	}
	for (int n = 0; n < count; n++)
	{
		element(n) = ptr[n]; //將ptr內的字元一個一個複製進當前陣列內(根據count的大小，element裡的myPtr()可能為bx.buf或bx.ptr)
	}
}

// fill constructor
string::string(const size_type count, const char ch) //count不包含空字元
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = count; //mySize == 字串長度
	if (count >= 16) //若傳進來的字串長度 >= 16
	{
		myRes += (count / 16) * 16; //算出一個倍數(count / 16)，將其乘以16後加入myRes(在fill constructor內的擴展規則)
		bx.ptr = new char[myRes]; //因count >= 16，故配置動態陣列
	}
	for (int n = 0; n < count; n++)
	{
		element(n) = ch; //將ch一個一個複製進當前陣列內
	}
}

// copy constructor
string::string(const string& right)
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = right.mySize; //mySize == right字串長度
	if (right.mySize >= 16) //若傳進來的字串長度 >= 16
	{
		myRes += (right.mySize / 16) * 16; //算出一個倍數(right.mySize / 16)，將其乘以16後加入myRes(在copy constructor內的擴展規則)
		bx.ptr = new char[myRes + 1]; //因right.mySize >= 16，故配置動態陣列，其空間 == myRes + 1空字元
	}
	for (int n = 0; n < right.mySize + 1; n++) //將right.element(n)內的值(包括空字元)複製進當前陣列內
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
	mySize = right.mySize; //mySize == right字串長度
	if (myRes < right.mySize) //若當前陣列的總空間數 < right的字串長度
	{
		if (myRes != 15) //若bx.ptr已有動態陣列(在myRes == 15時bx.ptr還未配置動態陣列)
		{
			delete[]bx.ptr; //則釋放舊陣列
		}
		myRes = ((right.mySize / 16) * 16 + 15 >= myRes * 3 / 2) ? (right.mySize / 16) * 16 + 15 : myRes * 3 / 2; //myRes在assign內的擴展規則
		bx.ptr = new char[myRes + 1]; //bx.ptr配置動態陣列，其空間 == myRes + 1空字元
	}
	for (int n = 0; n < right.mySize + 1; n++) //將right.element(n)內的值(包括空字元)複製進當前陣列內
	{
		element(n) = right.element(n);
	}
	return *this;
}

string::iterator string::insert(const_iterator where, const char ch)
{
	if (where >= myPtr() && where <= myPtr() + mySize)
	{
		if (mySize + 1 <= myRes) //若還有空間可以放入新元素
		{
			for (int a = mySize; a >= 0; a--)
			{
				if (myPtr() + a == where) //若myPtr()陣列上某位置 == 指定插入的地址
				{
					element(a) = ch; //將新元素加入該格陣列
					break; //插入完畢，跳出迴圈
				}
				element(a) = element(a - 1); //從最後一個元素開始，每次將該元素往後移1格
			}
		}
		else if (mySize == myRes)
		{
			int tempRes = (myRes < 32) ? myRes + 16 : myRes * 3 / 2; //宣告暫存Res，其值根據當前myRes的值而定(myRes在insert內的擴展規則)
			pointer temp = new char[tempRes + 1]; //宣告暫存動態陣列，其空間 == tempRes + 1空字元
			for (int a = 0, b = 0; a < mySize + 1; a++, b++)
			{
				if (myPtr() + a == where) //若myPtr()陣列上某位置 == 指定插入的地址
				{
					temp[a] = ch; //將新元素加入該格陣列
					b--; //此時element(b)的值未複製，若b不減1則該值不會被存入temp[a]中
					continue;
				}
				temp[a] = element(b); //將element(b)複製給temp
			}
			if (myRes != 15) //若bx.ptr已有動態陣列(在myRes == 15時bx.ptr還未配置動態陣列)
			{
				delete[]bx.ptr; //則釋放舊陣列
			}
			bx.ptr = temp; //將temp的地址給bx.ptr(使得bx.ptr指向temp的陣列)
			myRes = tempRes; //更新myRes的值
		}
		mySize++; //因插入1元素，故mySize + 1
		element(mySize) = '\0'; //在字串結尾放入空字元(但若不放也不會錯)
	}
	else
		return iterator(nullptr);
}

string::iterator string::erase(const_iterator where)
{
	if (where >= myPtr() && where < myPtr() + mySize)
	{
		for (int i = (where - myPtr()) + 1; i < mySize; i++) //(where - myPtr()) == 陣列上欲刪除的位置，i == 從該位置的下一格開始
		{
			element(i - 1) = element(i); //將之後的值全部往前移1格
		}
		mySize--; //因刪除1元素，故mySize - 1
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