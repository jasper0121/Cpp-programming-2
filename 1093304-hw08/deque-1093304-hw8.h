#ifndef DEQUE_H
#define DEQUE_H

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
	using size_type = typename MyDeque::size_type;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::const_pointer;
	using reference = const value_type&;

	// construct with null pointer
	DequeConstIterator()
		: myOff(0),
		myCont(nullptr)
	{
	}

	// construct with offset off in *pDeque
	DequeConstIterator(size_type off, const MyDeque* pDeque)
		: myOff(off),
		myCont(pDeque)
	{
	}

	DequeConstIterator(const DequeConstIterator& right) // copy constructor
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this) // avoid self-assignment
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this; // enables x = y = z, for example
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	DequeConstIterator& operator++() // preincrement
	{
		++myOff;
		return *this;
	}

	DequeConstIterator operator++(int) // postincrement
	{
		DequeConstIterator tmp = *this;
		++* this;
		return tmp;
	}

	DequeConstIterator& operator--() // predecrement
	{
		--myOff;
		return *this;
	}

	DequeConstIterator operator--(int) // postdecrement
	{
		DequeConstIterator tmp = *this;
		--* this;
		return tmp;
	}

	// increment by integer
	DequeConstIterator& operator+=(const difference_type off)
	{
		myOff += off;
		return *this;
	}

	// return this + integer
	DequeConstIterator operator+(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	// return this - integer
	DequeConstIterator operator-(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp -= off;
	}

	// return difference of iterators
	difference_type operator-(const DequeConstIterator& right) const
	{
		return (static_cast<difference_type>(this->myOff - right.myOff));
	}

	reference operator[](const difference_type off) const // subscript
	{
		return *(*this + off);
	}

	// test for iterator equality
	bool operator==(const DequeConstIterator& right) const
	{
		return this->myCont == right.myCont && this->myOff == right.myOff;
	}

	// test for iterator inequality
	bool operator!=(const DequeConstIterator& right) const
	{
		return !(*this == right);
	}

	// test if this < right
	bool operator<(const DequeConstIterator& right) const
	{
		return this->myOff < right.myOff;
	}

	// test if this > right
	bool operator>(const DequeConstIterator& right) const
	{
		return right < *this;
	}

	// test if this <= right
	bool operator<=(const DequeConstIterator& right) const
	{
		return !(right < *this);
	}

	// test if this >= right
	bool operator>=(const DequeConstIterator& right) const
	{
		return !(*this < right);
	}

	const MyDeque* myCont; // keep a pointer to deque
	size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	DequeIterator() // construct with null deque pointer
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque) // construct with offset off in *pDeque
	{
	}

	reference operator*() const // return designated object
	{
		return const_cast<reference>(MyBase::operator*());
	}

	pointer operator->() const // return pointer to class object
	{
		return const_cast<pointer>(MyBase::operator->());
		//      return &( operator*() );
	}

	DequeIterator& operator++() // preincrement
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator operator++(int) // postincrement
	{
		DequeIterator tmp = *this;
		MyBase::operator++();
		return tmp;
	}

	DequeIterator& operator--() // predecrement
	{
		MyBase::operator--();
		return *this;
	}

	DequeIterator operator--(int) // postdecrement
	{
		DequeIterator tmp = *this;
		MyBase::operator--();
		return tmp;
	}

	// increment by integer
	DequeIterator& operator+=(const difference_type off)
	{
		MyBase::operator+=(off);
		return *this;
	}

	// return this + integer
	DequeIterator operator+(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeIterator& operator-=(const difference_type off)
	{
		MyBase::operator-=(off);
		return *this;
	}

	using MyBase::operator-; // return difference of iterators

	// return this - integer
	DequeIterator operator-(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp -= off;
	}

	reference operator[](const difference_type off) const // subscript
	{
		return const_cast<reference>(MyBase::operator[](off));
	}
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using MapPtr = Ty**;

	DequeVal() // initialize values
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	// determine block from offset
	size_type getBlock(size_type off) const
	{
		return off % (4 * mapSize) / 4;
		//      return ( off / 4 ) & ( mapSize - 1 );
	}

	MapPtr map;        // pointer to array of pointers to blocks
	size_type mapSize; // size of map array, zero or 2^N
	size_type myOff;   // offset of initial element
	size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
	using MapPtr = Ty**;
	using ScaryVal = DequeVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = DequeIterator< ScaryVal >;
	using const_iterator = DequeConstIterator< ScaryVal >;

	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	// construct empty deque
	deque()
		: myData()
	{
	}

	// construct from count * val
	deque(size_type count, const value_type& val)
		: myData()
	{
		if (count == 0)
		{
			myData.map = nullptr;
			myData.mapSize = 0;
		}
		else
		{
			myData.mapSize = 8;
			while (count > 4 * (myData.mapSize - 1))
				myData.mapSize *= 2;

			myData.map = new value_type * [myData.mapSize]();
			for (size_type i = 0; i <= (count - 1) / 4; i++)
				myData.map[i] = new value_type[4];

			for (size_type i = 0; i < count; i++)
				myData.map[i / 4][i % 4] = val;
		}
		myData.mySize = count;
	}

	// destroy the deque
	~deque()
	{
		clear();
	}

	// return iterator for beginning of mutable sequence
	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	// return iterator for beginning of nonmutable sequence
	const_iterator begin() const
	{
		return const_iterator(myData.myOff, &myData);
	}

	// return iterator for end of mutable sequence
	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for end of nonmutable sequence
	const_iterator end() const
	{
		return const_iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for beginning of reversed mutable sequence
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	// return iterator for beginning of reversed nonmutable sequence
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	// return iterator for end of reversed mutable sequence
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	// return iterator for end of reversed nonmutable sequence
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// return iterator for beginning of nonmutable sequence
	const_iterator cbegin() const
	{
		return begin();
	}

	// return iterator for end of nonmutable sequence
	const_iterator cend() const
	{
		return end();
	}

	// return iterator for beginning of reversed nonmutable sequence
	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}

	// return iterator for end of reversed nonmutable sequence
	const_reverse_iterator crend() const
	{
		return rend();
	}

	// return length of sequence
	size_type size() const
	{
		return myData.mySize;
	}

	// test if sequence is empty
	bool empty() const
	{
		return myData.mySize == 0;
	}

	const_reference operator[](size_type pos) const
	{
		return *(begin() + static_cast<difference_type>(pos));
	}

	reference operator[](size_type pos)
	{
		return *(begin() + static_cast<difference_type>(pos));
	}

	reference front()
	{
		return *begin();
	}

	const_reference front() const
	{
		return *begin();
	}

	reference back()
	{
		return *(end() - 1);
	}

	const_reference back() const
	{
		return *(end() - 1);
	}

	// insert val at where
	void insert(const_iterator where, const value_type& val)
	{
		if (myData.mySize == 0)
		{
			if (where == begin() && where == end())
			{
				if (myData.mapSize == 0) //當mySize == 0且mapSize == 0時
				{
					myData.map = new pointer[8](); //建立每格都是pointer的動態陣列
					myData.map[7] = new value_type[4]; //map的最後一格再建立每格都是value_type的動態陣列
					myData.map[7][3] = val; //在最後一列的最後一格放入初始值
					myData.mapSize = 8;
					myData.myOff = 31;
				}
				else //當mySize == 0但mapSize != 0時(erase導致)
				{
					size_t capacity = 4 * myData.mapSize; //陣列總格數
					myData.map[(capacity - 1) / 4][3] = val; //在最後一列的最後一格放入初始值
					myData.myOff = capacity - 1;
				}
			}
		}
		else
		{
			if (begin() <= where && where <= end())
			{
				// all elements before where move forward
				if (where <= begin() + myData.mySize / 2)
				{
					size_type newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					if (newFront % 4 == 3 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					}
					//----------------------------------------------------------------------------------------------------------------------------------------------------------
					size_t capacity = 4 * myData.mapSize; //陣列總格數
					size_t insert_place = (where.myOff - 1) % capacity; //實際應insert的位置
					if (myData.map[newFront / 4] == nullptr) //若newFront所在列還未建立動態陣列
					{
						myData.map[newFront / 4] = new value_type[4];
					}

					for (size_t pos = newFront; pos != insert_place; (++pos) %= capacity) //每次pos先 + 1後再取餘數
					{
						myData.map[pos / 4][pos % 4] = myData.map[(pos + 1) % capacity / 4][(pos + 1) % 4]; //將where之前的元素往前移(不包含where)
					}

					myData.map[insert_place / 4][insert_place % 4] = val; //在正確位置insert
					myData.myOff = newFront; //newFront == insert後myOff的位置
					//----------------------------------------------------------------------------------------------------------------------------------------------------------
				}
				else // all elements after (and at) where move backward
				{
					size_type newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
					if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newBack = myData.myOff + myData.mySize;
					}
					//----------------------------------------------------------------------------------------------------------------------------------------------------------
					size_t capacity = 4 * myData.mapSize; //陣列總格數
					size_t insert_place = where.myOff % capacity; //實際應insert的位置
					if (myData.map[newBack / 4] == nullptr) //若newBack所在列還未建立動態陣列
					{
						myData.map[newBack / 4] = new value_type[4];
					}

					for (size_t pos = newBack; pos != insert_place; (--pos) %= capacity) //每次pos先 - 1後再取餘數
					{
						myData.map[pos / 4][pos % 4] = myData.map[(pos - 1) % capacity / 4][(pos - 1) % 4]; //將where之後的元素往後移(包含where)
					}

					myData.map[insert_place / 4][insert_place % 4] = val; //在正確位置insert
					myData.myOff %= capacity; //若在insert前先erase，則myOff可能超過capacity，故要將myOff限制在capacity內
					//----------------------------------------------------------------------------------------------------------------------------------------------------------
				}
			}
		}

		++myData.mySize;
	}

	// erase element at where
	void erase(const_iterator where)
	{
		if (myData.mySize > 0 && begin() <= where && where < end())
		{
			if (myData.mySize == 1 && begin() == where)
			{
				myData.myOff = 0;
				myData.mySize = 0;
			}
			else
			{
				size_t capacity = 4 * myData.mapSize; //陣列總格數
				// all elements before where move backward
				if (where < begin() + myData.mySize / 2)
				{
					//where和myData的myOff可能超過capacity，故要將myOff限制在capacity內
					for (size_t pos = where.myOff % capacity; pos != myData.myOff % capacity; (--pos) %= capacity)
					{
						myData.map[pos / 4][pos % 4] = myData.map[(pos - 1) % capacity / 4][(pos - 1) % 4]; //將where之前的元素往後移
					}

					myData.myOff++; //在前半erase會讓myOff + 1，且STL的做法不取餘數
				}
				else // all elements after where move forward
				{
					//where和myData的myOff可能超過capacity，故要將myOff限制在capacity內
					for (size_t pos = where.myOff % capacity; pos != (myData.myOff + myData.mySize - 1) % capacity; (++pos) %= capacity)
					{
						myData.map[pos / 4][pos % 4] = myData.map[(pos + 1) % capacity / 4][(pos + 1) % 4]; //將where之後的元素往前移
					}
				}

				--myData.mySize;
			}
		}
	}

	// erase all
	void clear()
	{
		if (myData.mapSize > 0)
		{
			for (size_type i = 0; i < myData.mapSize; i++)
				if (myData.map[i] != nullptr)
					delete[] myData.map[i];
			delete[] myData.map;

			myData.mapSize = 0;
			myData.mySize = 0;
			myData.myOff = 0;
			myData.map = MapPtr();
		}
	}

private:

	// determine block from offset

	size_type getBlock(size_type off) const
	{
		return myData.getBlock(off);
		//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
	}

	void doubleMapSize()
	{
		if (myData.mapSize > 0)
		{
			MapPtr temp = new pointer[myData.mapSize * 2](); //建立每格都是pointer的動態陣列，空間為原本的2倍
			for (size_t row = myData.myOff / 4; row < myData.myOff / 4 + myData.mapSize; row++) //從myData.myOff的所在列開始
			{
				temp[row] = myData.map[row % myData.mapSize]; //每次將該列的地址存入temp上相對應的位置
			}

			delete[]myData.map; //釋放舊陣列
			myData.map = temp; //指向新陣列
			myData.mapSize *= 2; //空間翻倍
		}
	}

	ScaryVal myData;
};

#endif