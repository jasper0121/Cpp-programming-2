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
			myData.myFirst = new value_type[count](); //myFirst�إ߰ʺA�}�C�A�ñN�C��}�C����ƪ�l�Ƭ�0
			myData.myLast = myData.myEnd = myData.myFirst + count; //myLast == myEnd == myFirst + �`�Ŷ���
		}
	}

	// copy constructor
	// Constructs a vector with a copy of each of the elements in "right",
	// in the same order.
	vector(const vector& right)
		: myData()
	{
		size_t rightSize = right.myData.myLast - right.myData.myFirst; //right���������Ӽ�
		myData.myFirst = new value_type[rightSize]; //�إ߷s�ʺA�}�C�A���`��Ƭ�right�������Ӽ�
		myData.myLast = myData.myEnd = myData.myFirst + rightSize; //�]STL vector�u�ƻs�������������A�GmyLast == myEnd
		for (size_t n = 0; n < rightSize; n++)
		{
			myData.myFirst[n] = right.myData.myFirst[n]; //�ƻs�}�C������
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
			if (size() == capacity()) //�Y�C�ӪŶ���������(�S���Ŷ���J�s����)
			{
				pointer temp = myData.myFirst; //�ŧi�Ȧs�ë��VmyFirst�}�C
				int old_length = capacity(); //�������J�e�°}�C�`����
				int new_length = (capacity() <= 1) ? old_length + 1 : old_length * 3 / 2; //�`���� <= 1�ɡA�s�ʺA�}�C���� == �ª��� + 1�A�Ϥ� == �ª��� * 1.5��
				myData.myFirst = new value_type[new_length]; //���s�t�m
				for (int a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst��e�}�C�s���Ab == temp��e�}�C�s���Aold_length + 1 == �s�����`����
				{
					if (temp + a == where.ptr) //�Ytemp�}�C�W�Y��m == ���w���J���a�}
					{
						myData.myFirst[a] = val; //�h�N�s�����[�J�Ӯ�}�C
						b--; //����temp[b]���ȥ��ƻs�A�Yb����1�h�ӭȤ��|�Q�s�JmyFirst[a]��
						continue;
					}
					myData.myFirst[a] = temp[b]; //�Ntemp���������ƻs����e�}�C
				}
				myData.myLast = myData.myFirst + old_length + 1; //myLast == myFirst + �°}�C�`���� + ���J1�s����
				myData.myEnd = myData.myFirst + new_length; //myEnd == myFirst + �s�}�C�`����
				delete[]temp; //����Ȧs���O����
			}
			else //�Y�٦��Ŷ��i�H��J�s����(�Ysize() < capacity())
			{
				for (int c = size(); c >= 0; c--) //�]�|��1�s�����[�J�A�G�@�}�lc == size()�ӫDsize() - 1
				{
					if (myData.myFirst + c == where.ptr) //�YmyFirst�}�C�W�Y��m == ���w���J���a�}
					{
						myData.myFirst[c] = val; //�N�s�����[�J�Ӯ�}�C
						myData.myLast++; //�]���J1��A�GmyLast����᭱1��(������1�檺�a�})
						break; //���J�����A���X�j��
					}
					myData.myFirst[c] = myData.myFirst[c - 1]; //�q�̫�@�Ӥ����}�l�A�C���N�Ӥ������Ჾ1��
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
			size_t rightSize = right.myData.myLast - right.myData.myFirst; //right���������Ӽ�
			if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //�Y��e�Ŷ������Hassign�A���X�i�Ŷ���h�i�H��
			{
				size_t new_length = capacity() * 3 / 2; //�s�ʺA�}�C�Ŷ��� == �ªŶ���*1.5��
				delete[]myData.myFirst; //�����°}�C
				myData.myFirst = new value_type[new_length]; //���s�t�m
				myData.myEnd = myData.myFirst + new_length; //myEnd == myFirst + �`�Ŷ���
			}
			else if (rightSize > capacity() * 3 / 2) //�Y�X�i�Ŷ��ᤴ�����Hassign
			{
				delete[]myData.myFirst; //�����°}�C
				myData.myFirst = new value_type[rightSize]; //���s�t�m(�Ŷ���right�������Ӽ�)
				myData.myEnd = myData.myFirst + rightSize; //myEnd == myFirst + right����������
			}

			for (size_t i = 0; i < rightSize; i++) //�Nright���������ƻs����e�}�C
			{
				myData.myFirst[i] = right.myData.myFirst[i];
			}
			myData.myLast = myData.myFirst + rightSize; //myLast == myFirst + right����������
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
			for (size_t i = (where.ptr - myData.myFirst) + 1; i < size(); i++) //(where.ptr - myFirst) == �}�C�W���R������m�Ai == �q�Ӧ�m���U�@��}�l
			{
				myData.myFirst[i - 1] = myData.myFirst[i]; //�N���᪺�ȥ������e��1��
			}
			myData.myLast--; //�]�R��1��A�GmyLast����e��1��(�����e1�檺�a�})
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

	//�]left�Mright���Oconst�A�G�]leftPtr�MrightPtr���Oconst_iterator
	for (typename vector<Ty>::const_iterator leftPtr = --left.end(), rightPtr = --right.end(); leftPtr != --left.begin(); leftPtr--, rightPtr--)
	{
		if (*leftPtr != *rightPtr)
		{
			return false;
		}
	}

	return true; //�వ�즹�N��2vector�۵�
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=(const vector< Ty >& left, const vector< Ty >& right)
{
	return !(left == right);
}

#endif // VECTOR_H