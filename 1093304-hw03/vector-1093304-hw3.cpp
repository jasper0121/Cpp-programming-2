#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
	: myFirst(),
	myLast(),
	myEnd()
{
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
vector::vector(const vector& right)
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
vector::iterator vector::insert(const_iterator where, const value_type& val)
{
	if (size() == capacity()) //若每個空間都有元素(沒有空間放入新元素)
	{
		pointer temp = myFirst; //宣告暫存並指向myFirst陣列
		int old_length = capacity(); //紀錄插入前舊陣列總長度
		int new_length = (capacity() <= 1) ? old_length + 1 : old_length * 3 / 2; //總長度 <= 1時，新動態陣列長度 == 舊長度 + 1，反之 == 舊長度 * 1.5倍
		myFirst = new int[new_length]; //重新配置
		for (int a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst當前陣列編號，b == temp當前陣列編號，old_length + 1 == 新元素總長度
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
	else //若還有空間可以放入新元素(即size() < capacity())
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
	return myFirst;
}

// overloaded assignment operator
// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector& right)
{
	if (this != &right) // avoid self-assignment
	{
		size_t rightSize = right.myLast - right.myFirst; //right內的元素個數
		if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //若當前空間不足以assign，但擴展空間後則可以時
		{
			size_t new_length = capacity() * 3 / 2; //新動態陣列空間數 == 舊空間數*1.5倍
			delete[]myFirst; //釋放舊陣列
			myFirst = new int[new_length]; //重新配置
			myEnd = myFirst + new_length; //myEnd == myFirst + 總空間數
		}
		else if (rightSize > capacity() * 3 / 2) //若擴展空間後仍不足以assign
		{
			delete[]myFirst; //釋放舊陣列
			myFirst = new int[rightSize]; //重新配置(空間為right的元素個數)
			myEnd = myFirst + rightSize; //myEnd == myFirst + right的元素長度
		}

		for (size_t i = 0; i < rightSize; i++) //將right內的元素複製給當前陣列
		{
			myFirst[i] = right.myFirst[i];
		}
		myLast = myFirst + rightSize; //myLast == myFirst + right的元素長度
	}

	return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where)
{
	for (size_t i = (where - myFirst) + 1; i < size(); i++) //(where - myFirst) == 陣列上欲刪除的位置，i == 從該位置的下一格開始
	{
		myFirst[i - 1] = myFirst[i]; //將之後的值全部往前移1格
	}
	myLast--; //因刪除1格，故myLast改指前面1格(紀錄前1格的地址)
	return myFirst;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear() // erase all
{
	myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
	return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
	return const_iterator(myFirst);
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

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
	return const_iterator(myLast);
}

// Returns a const_iterator pointing to the first element in the container.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::cbegin() const
{
	return begin();
}

// Returns a const_iterator pointing to the past-the-end element in the container.
// If the container is empty, this function returns the same as vector::cbegin.
// The value returned shall not be dereferenced.
vector::const_iterator vector::cend() const
{
	return end();
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
	return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
	return static_cast<size_type>(myLast - myFirst);
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
	return static_cast<size_type>(myEnd - myFirst);
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::front()
{
	return *myFirst;
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::front() const
{
	return *myFirst;
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::back()
{
	return myLast[-1];
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::back() const
{
	return myLast[-1];
}