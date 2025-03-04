#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
	myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count)
{
	myFirst = new int[count](); //myFirst建立動態陣列，並將每格陣列內資料初始化為0
	myLast = myEnd = myFirst + count; //myLast == myEnd == myFirst + 總空間數
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector& right) //STL vector複製陣列時只複製有元素的部分
{
	size_type rightSize = right.myLast - right.myFirst; //right內的元素個數
	myFirst = new int[rightSize]; //建立新動態陣列，其總格數為right的元素個數
	myLast = myEnd = myFirst + rightSize; //因STL vector只複製有元素的部分，故myLast == myEnd
	for (size_type n = 0; n < rightSize; n++)
	{
		myFirst[n] = right.myFirst[n]; //複製陣列內的值
	}
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
	if (myFirst != nullptr)
		delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert(const_iterator where, const value_type& val) //const_iterator == const int*
{
	if (myFirst == nullptr) //若myFirst還未建立動態陣列
	{
		myFirst = new int[1]; //則配置動態陣列(1格)
		myFirst[0] = val;
		myLast = myEnd = myFirst + 1; //myLast == myEnd == myFirst + 1
	}
	else
	{
		if (size() == 1 && capacity() == 1) //若空間只有1格且該格內有元素
		{
			pointer temp = myFirst; //宣告暫存並指向myFirst陣列(pointer == int*)
			myFirst = new int[2]; //重新配置(2格)
			if (temp == where) //若舊陣列(暫存)的首格地址 == 元素指定加入的地址
			{
				myFirst[0] = val; //則將新元素加入0號陣列
				myFirst[1] = temp[0];
			}
			else
			{
				myFirst[0] = temp[0];
				myFirst[1] = val; //否則將新元素加入1號陣列
			}
			myLast = myEnd = myFirst + 2; //myLast == myEnd == myFirst + 2
			delete[]temp; //釋放暫存的記憶體
		}
		else if (size() == capacity()) //若每個空間都有元素(沒有空間放入新元素)
		{
			pointer temp = myFirst; //宣告暫存並指向myFirst陣列
			size_t old_length = capacity(); //紀錄插入前舊陣列總長度
			size_t new_length = old_length * 3 / 2; //總長度 >= 2時，新動態陣列長度 == 舊長度 * 1.5倍
			myFirst = new int[new_length]; //重新配置
			for (size_t a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst當前陣列編號，b == temp當前陣列編號，old_length + 1 == 新元素總長度
			{
				if (temp + a == where) //若temp陣列上某位置 == 指定插入的地址
				{
					myFirst[a] = val; //則將新元素加入該格陣列
					b--; //此時temp[b]的值未複製，若b不減1則該值不會被存入myFirst[a]中
					continue;
				}
				myFirst[a] = temp[b]; //將temp內的元素複製給當前陣列
			}
			myLast = myFirst + old_length + 1; //myLast == myFirst + 舊陣列總長度+插入1新元素
			myEnd = myFirst + new_length; //myEnd == myFirst + 新陣列總長度
			delete[]temp; //釋放暫存的記憶體
		}
		else if (size() < capacity()) //若還有空間可以放入新元素
		{
			for (int c = size(); c >= 0; c--) //因會有1新元素加入，故一開始c == size()而非size() - 1
			{
				if (myFirst + c == where) //若myFirst陣列上某位置 == 指定插入的地址
				{
					myFirst[c] = val; //將新元素加入該格陣列
					myLast++; //因插入1格，故myLast改指後面1格(紀錄後1格的地址)
					break; //插入完畢，跳出迴圈
				}
				myFirst[c] = myFirst[c - 1]; //從最後一個元素開始，每次將該元素往後移1格
			}
		}
	}
	return myFirst;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector& right)
{
	size_t rightSize = right.myLast - right.myFirst; //right內的元素長度

	if (capacity() >= rightSize) //若有足夠空間可以assign
	{
		for (size_t a = 0; a < rightSize; a++) //則將right內的元素複製給當前陣列
		{
			myFirst[a] = right.myFirst[a];
		}
	}
	else if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //若當前空間不足以assign，但擴展空間後則可以時
	{
		size_t new_length = capacity() * 3 / 2; //新動態陣列空間數 == 舊空間數*1.5倍
		delete[]myFirst; //釋放舊陣列
		myFirst = new int[new_length]; //重新配置
		for (size_t b = 0; b < rightSize; b++) //將right內的元素複製給當前陣列
		{
			myFirst[b] = right.myFirst[b];
		}
		myEnd = myFirst + new_length; //myEnd == myFirst + 總空間數
	}
	else if (rightSize > capacity() * 3 / 2) //若擴展空間後仍不足以assign
	{
		delete[]myFirst; //釋放舊陣列
		myFirst = new int[rightSize]; //重新配置(空間為right的元素個數)
		for (size_t c = 0; c < rightSize; c++) //將right內的元素複製給當前陣列
		{
			myFirst[c] = right.myFirst[c];
		}
		myEnd = myFirst + rightSize; //myEnd == myFirst + right的元素長度
	}
	myLast = myFirst + rightSize; //myLast == myFirst + right的元素長度
	return *this; //回傳當前的物件
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where)
{
	for (int a = 0; a < size(); a++)
	{
		if (myFirst + a == where) //若myFirst陣列上某位置 == 指定刪除的地址
		{
			for (int b = a + 1; b < size(); b++) //則從下1格開始
			{
				myFirst[b - 1] = myFirst[b]; //將之後的值全部往前移1格
			}
			break; //刪除完畢，跳出迴圈
		}
	}
	myLast--; //因刪除1格，故myLast改指前面1格(紀錄前1格的地址)
	return myFirst;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
	myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
	return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
	return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty()
{
	return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
	return static_cast<size_type>(myLast - myFirst);
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
	return static_cast<size_type>(myEnd - myFirst);
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element(const size_type pos)
{
	return myFirst[pos];
}