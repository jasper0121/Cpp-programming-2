// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::const_pointer;
	using reference = const value_type&;
	using TPtr = typename MyVec::pointer;

	VectorConstIterator()
		: ptr()
	{
	}

	VectorConstIterator(TPtr parg)
		: ptr(parg)
	{
	}

	reference operator*() const
	{
		return *ptr;
	}

	pointer operator->() const
	{
		return ptr;
	}

	VectorConstIterator& operator++()
	{
		++ptr;
		return *this;
	}

	VectorConstIterator operator++(int)
	{
		VectorConstIterator temp = *this;
		++* this;
		return temp;
	}

	VectorConstIterator& operator--()
	{
		--ptr;
		return *this;
	}

	VectorConstIterator operator--(int)
	{
		VectorConstIterator temp = *this;
		--* this;
		return temp;
	}

	VectorConstIterator& operator+=(const difference_type off)
	{
		ptr += off;
		return *this;
	}

	VectorConstIterator operator+(const difference_type off) const
	{
		VectorConstIterator temp = *this;
		return temp += off;
	}

	VectorConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	VectorConstIterator operator-(const difference_type off) const
	{
		VectorConstIterator temp = *this;
		return temp -= off;
	}

	difference_type operator-(const VectorConstIterator& right) const
	{
		return ptr - right.ptr;
	}

	reference operator[](const difference_type off) const
	{
		return *(*this + off);
	}

	bool operator==(const VectorConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VectorConstIterator& right) const
	{
		return !(*this == right);
	}

	bool operator<(const VectorConstIterator& right) const
	{
		return ptr < right.ptr;
	}

	bool operator>(const VectorConstIterator& right) const
	{
		return right < *this;
	}

	bool operator<=(const VectorConstIterator& right) const
	{
		return !(right < *this);
	}

	bool operator>=(const VectorConstIterator& right) const
	{
		return !(*this < right);
	}

	TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator
{
public:
	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::const_pointer;
	using reference = value_type&;
	using TPtr = typename MyVec::pointer;

	VectorIterator()
		: ptr()
	{
	}

	VectorIterator(TPtr parg)
		: ptr(parg)
	{
	}

	reference operator*() const
	{
		return *ptr;
	}

	pointer operator->() const
	{
		return ptr;
	}

	VectorIterator& operator++()
	{
		++ptr;
		return *this;
	}

	VectorIterator operator++(int)
	{
		VectorIterator temp = *this;
		++* this;
		return temp;
	}

	VectorIterator& operator--()
	{
		--ptr;
		return *this;
	}

	VectorIterator operator--(int)
	{
		VectorIterator temp = *this;
		--* this;
		return temp;
	}

	VectorIterator& operator+=(const difference_type off)
	{
		ptr += off;
		return *this;
	}

	VectorIterator operator+(const difference_type off) const
	{
		VectorIterator temp = *this;
		return temp += off;
	}

	VectorIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	VectorIterator operator-(const difference_type off) const
	{
		VectorIterator temp = *this;
		return temp -= off;
	}

	difference_type operator-(const VectorIterator& right) const
	{
		return ptr - right.ptr;
	}

	reference operator[](const difference_type off) const
	{
		return *(*this + off);
	}

	bool operator==(const VectorIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VectorIterator& right) const
	{
		return !(*this == right);
	}

	bool operator<(const VectorIterator& right) const
	{
		return ptr < right.ptr;
	}

	bool operator>(const VectorIterator& right) const
	{
		return right < *this;
	}

	bool operator<=(const VectorIterator& right) const
	{
		return !(right < *this);
	}

	bool operator>=(const VectorIterator& right) const
	{
		return !(*this < right);
	}

	TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
	using value_type = ValueType;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	VectorVal()
		: myFirst(),
		myLast(),
		myEnd()
	{
	}

	pointer myFirst; // pointer to beginning of array
	pointer myLast;  // pointer to current end of sequence
	pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
	using value_type = Ty;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = Ty&;
	using const_reference = const Ty&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

private:
	using ScaryVal = VectorVal< Ty >;

public:
	using iterator = VectorIterator< ScaryVal >;
	using const_iterator = VectorConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	// empty vector constructor (default constructor)
	// Constructs an empty vector, with no elements.
	vector()
		: myData()
	{
	}

	// fill constructor
	// Constructs a vector with "count" elements.
	// Each element is initialized as 0.
	vector(const size_type count)
		: myData()
	{
		if (count != 0)
		{
			myData.myFirst = new value_type[count](); //myFirst建立動態陣列，並將每格陣列內資料初始化為0
			myData.myLast = myData.myEnd = myData.myFirst + count; //myLast == myEnd == myFirst + 總空間數
		}
	}

	// copy constructor
	// Constructs a vector with a copy of each of the elements in "right",
	// in the same order.
	vector(const vector& right)
		: myData()
	{
		size_t rightSize = right.myData.myLast - right.myData.myFirst; //right內的元素個數
		myData.myFirst = new value_type[rightSize]; //建立新動態陣列，其總格數為right的元素個數
		myData.myLast = myData.myEnd = myData.myFirst + rightSize; //因STL vector只複製有元素的部分，故myLast == myEnd
		for (size_t n = 0; n < rightSize; n++)
		{
			myData.myFirst[n] = right.myData.myFirst[n]; //複製陣列內的值
		}
	}

	// Vector destructor
	// Destroys the vector object.
	// Deallocates all the storage capacity allocated by the vector.
	~vector()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	// The vector is extended by inserting a new element before the element
	// at the specified position, effectively increasing the vector size by one.
	// This causes an automatic reallocation of the allocated storage space
	// if and only if the new vector size surpasses the current vector capacity.
	// Relocates all the elements that were after "where" to their new positions.
	iterator insert(const_iterator where, const Ty& val)
	{
		if (where.ptr >= myData.myFirst && where.ptr <= myData.myLast)
		{
			if (size() == capacity()) //若每個空間都有元素(沒有空間放入新元素)
			{
				pointer temp = myData.myFirst; //宣告暫存並指向myFirst陣列
				int old_length = capacity(); //紀錄插入前舊陣列總長度
				int new_length = (capacity() <= 1) ? old_length + 1 : old_length * 3 / 2; //總長度 <= 1時，新動態陣列長度 == 舊長度 + 1，反之 == 舊長度 * 1.5倍
				myData.myFirst = new value_type[new_length]; //重新配置
				for (int a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst當前陣列編號，b == temp當前陣列編號，old_length + 1 == 新元素總長度
				{
					if (temp + a == where.ptr) //若temp陣列上某位置 == 指定插入的地址
					{
						myData.myFirst[a] = val; //則將新元素加入該格陣列
						b--; //此時temp[b]的值未複製，若b不減1則該值不會被存入myFirst[a]中
						continue;
					}
					myData.myFirst[a] = temp[b]; //將temp內的元素複製給當前陣列
				}
				myData.myLast = myData.myFirst + old_length + 1; //myLast == myFirst + 舊陣列總長度 + 插入1新元素
				myData.myEnd = myData.myFirst + new_length; //myEnd == myFirst + 新陣列總長度
				delete[]temp; //釋放暫存的記憶體
			}
			else //若還有空間可以放入新元素(即size() < capacity())
			{
				for (int c = size(); c >= 0; c--) //因會有1新元素加入，故一開始c == size()而非size() - 1
				{
					if (myData.myFirst + c == where.ptr) //若myFirst陣列上某位置 == 指定插入的地址
					{
						myData.myFirst[c] = val; //將新元素加入該格陣列
						myData.myLast++; //因插入1格，故myLast改指後面1格(紀錄後1格的地址)
						break; //插入完畢，跳出迴圈
					}
					myData.myFirst[c] = myData.myFirst[c - 1]; //從最後一個元素開始，每次將該元素往後移1格
				}
			}

			return myData.myFirst;
		}
		else
			return iterator(nullptr);
	}

	// overloaded assignment operator
	// Assigns new contents to the vector, replacing its current contents,
	// and modifying its size accordingly.
	// Copies all the elements from "right" into the vector
	// (with "right" preserving its contents).
	vector& operator=(const vector& right)
	{
		if (this != &right) // avoid self-assignment
		{
			size_t rightSize = right.myData.myLast - right.myData.myFirst; //right內的元素個數
			if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //若當前空間不足以assign，但擴展空間後則可以時
			{
				size_t new_length = capacity() * 3 / 2; //新動態陣列空間數 == 舊空間數*1.5倍
				delete[]myData.myFirst; //釋放舊陣列
				myData.myFirst = new value_type[new_length]; //重新配置
				myData.myEnd = myData.myFirst + new_length; //myEnd == myFirst + 總空間數
			}
			else if (rightSize > capacity() * 3 / 2) //若擴展空間後仍不足以assign
			{
				delete[]myData.myFirst; //釋放舊陣列
				myData.myFirst = new value_type[rightSize]; //重新配置(空間為right的元素個數)
				myData.myEnd = myData.myFirst + rightSize; //myEnd == myFirst + right的元素長度
			}

			for (size_t i = 0; i < rightSize; i++) //將right內的元素複製給當前陣列
			{
				myData.myFirst[i] = right.myData.myFirst[i];
			}
			myData.myLast = myData.myFirst + rightSize; //myLast == myFirst + right的元素長度
		}

		return *this; // enables x = y = z, for example
	}

	// Removes from the vector either a single element (where).
	// This effectively reduces the vector size by one, which is destroyed.
	// Relocates all the elements after the element erased to their new positions.
	iterator erase(const_iterator where)
	{
		if (where.ptr >= myData.myFirst && where.ptr < myData.myLast)
		{
			for (size_t i = (where.ptr - myData.myFirst) + 1; i < size(); i++) //(where.ptr - myFirst) == 陣列上欲刪除的位置，i == 從該位置的下一格開始
			{
				myData.myFirst[i - 1] = myData.myFirst[i]; //將之後的值全部往前移1格
			}
			myData.myLast--; //因刪除1格，故myLast改指前面1格(紀錄前1格的地址)
			return iterator(where.ptr);
		}
		else
			return iterator(nullptr);
	}

	// Removes all elements from the vector (which are destroyed),
	// leaving the vector with a size of 0.
	// A reallocation is not guaranteed to happen,
	// andthe vector capacity is not guaranteed to change due to calling this function.
	void clear()
	{
		myData.myLast = myData.myFirst;
	}

	// Returns an iterator pointing to the first element in the vector.
	// If the vector is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return iterator(myData.myFirst);
	}

	// Returns a const_iterator pointing to the first element in the vector.
	// If the vector is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myFirst);
	}

	// Returns an iterator referring to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the vector is empty, this function returns the same as vector::begin.
	iterator end()
	{
		return iterator(myData.myLast);
	}

	// Returns a const_iterator referring to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the vector is empty, this function returns the same as vector::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myLast);
	}

	// Returns a reverse iterator pointing to the last element in the vector
	// (i.e., its reverse beginning).
	// rbegin points to the element right before the one
	// that would be pointed to by member end.
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	// Returns a reverse iterator pointing to the last element in the vector
	// (i.e., its reverse beginning).
	// rbegin points to the element right before the one
	// that would be pointed to by member end.
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	// Returns a reverse iterator pointing to the theoretical element
	// preceding the first element in the vector
	// (which is considered its reverse end).
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	// Returns a reverse iterator pointing to the theoretical element
	// preceding the first element in the vector
	// (which is considered its reverse end).
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// Returns a const_iterator pointing to the first element in the vector.
	// If the vector is empty, the returned iterator value shall not be dereferenced.
	const_iterator cbegin() const
	{
		return begin();
	}

	// Returns a const_iterator pointing to the past-the-end element in the vector.
	// If the vector is empty, this function returns the same as vector::cbegin.
	// The value returned shall not be dereferenced.
	const_iterator cend() const
	{
		return end();
	}

	// Returns a const_reverse_iterator pointing to the last element in the vector
	// (i.e., its reverse beginning).
	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}

	// Returns a const_reverse_iterator pointing to the theoretical element
	// preceding the first element in the vector
	// (which is considered its reverse end).
	const_reverse_iterator crend() const
	{
		return rend();
	}

	// Returns whether the vector is empty (i.e. whether its size is 0).
	bool empty() const
	{
		return myData.myFirst == myData.myLast;
	}

	// Returns the number of elements in the vector.
	// This is the number of actual objects held in the vector,
	// which is not necessarily equal to its storage capacity.
	size_type size() const
	{
		return static_cast<size_type>(myData.myLast - myData.myFirst);
	}

	// Returns the size of the storage space currently allocated for the vector,
	// expressed in terms of elements.
	// This capacity is not necessarily equal to the vector size.
	// It can be equal or greater, with the extra space allowing to accommodate
	// for growth without the need to reallocate on each insertion.
	size_type capacity() const
	{
		return static_cast<size_type>(myData.myEnd - myData.myFirst);
	}

	// Returns a reference to the element at position "pos" in the vector.
	value_type& operator[](const size_type pos)
	{
		if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
		{
			cout << "vector subscript out of range\n";
			exit(1);
		}

		return myData.myFirst[pos];
	}

	// Returns a reference to the element at position "pos" in the vector.
	const value_type& operator[](const size_type pos) const
	{
		if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
		{
			cout << "vector subscript out of range\n";
			exit(1);
		}

		return myData.myFirst[pos];
	}

	// Returns a reference to the first element in the vector.
	// Calling this function on an empty vector causes undefined behavior.
	value_type& front()
	{
		return *myData.myFirst;
	}

	// Returns a reference to the first element in the vector.
	// Calling this function on an empty vector causes undefined behavior.
	const value_type& front() const
	{
		return *myData.myFirst;
	}

	// Returns a reference to the last element in the vector.
	// Calling this function on an empty vector causes undefined behavior.
	value_type& back()
	{
		return myData.myLast[-1];
	}

	// Returns a reference to the last element in the vector.
	// Calling this function on an empty vector causes undefined behavior.
	const value_type& back() const
	{
		return myData.myLast[-1];
	}

private:

	ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const vector< Ty >& left, const vector< Ty >& right)
{
	if (left.size() != right.size())
	{
		return false;
	}

	//因left和right都是const，故設leftPtr和rightPtr都是const_iterator
	for (typename vector<Ty>::const_iterator leftPtr = --left.end(), rightPtr = --right.end(); leftPtr != --left.begin(); leftPtr--, rightPtr--)
	{
		if (*leftPtr != *rightPtr)
		{
			return false;
		}
	}

	return true; //能做到此代表2vector相等
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=(const vector< Ty >& left, const vector< Ty >& right)
{
	return !(left == right);
}

#endif // VECTOR_H