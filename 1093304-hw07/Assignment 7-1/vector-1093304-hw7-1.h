// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

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
	using iterator = value_type*;
	using const_iterator = const value_type*;

	// empty container constructor (default constructor)
	// Constructs an empty container, with no elements.
	vector()
		: myData()
	{
	}

	// fill constructor
	// Constructs a container with "count" elements.
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
	// Constructs a container with a copy of each of the elements in "right",
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
	// Destroys the container object.
	// Deallocates all the storage capacity allocated by the vector.
	~vector()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	// The vector is extended by inserting a new element before the element
	// at the specified position, effectively increasing the container size by one.
	// This causes an automatic reallocation of the allocated storage space
	// if and only if the new vector size surpasses the current vector capacity.
	// Relocates all the elements that were after "where" to their new positions.
	iterator insert(const_iterator where, const value_type& val)
	{
		if (where >= myData.myFirst && where <= myData.myLast)
		{
			if (size() == capacity()) //�Y�C�ӪŶ���������(�S���Ŷ���J�s����)
			{
				pointer temp = myData.myFirst; //�ŧi�Ȧs�ë��VmyFirst�}�C
				int old_length = capacity(); //�������J�e�°}�C�`����
				int new_length = (capacity() <= 1) ? old_length + 1 : old_length * 3 / 2; //�`���� <= 1�ɡA�s�ʺA�}�C���� == �ª��� + 1�A�Ϥ� == �ª��� * 1.5��
				myData.myFirst = new value_type[new_length]; //���s�t�m
				for (int a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst��e�}�C�s���Ab == temp��e�}�C�s���Aold_length + 1 == �s�����`����
				{
					if (temp + a == where) //�Ytemp�}�C�W�Y��m == ���w���J���a�}
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
					if (myData.myFirst + c == where) //�YmyFirst�}�C�W�Y��m == ���w���J���a�}
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
			return nullptr;
	}

	// overloaded assignment operator
	// Assigns new contents to the container, replacing its current contents,
	// and modifying its size accordingly.
	// Copies all the elements from "right" into the container
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

	// Removes from the vector a single element (where).
	// This effectively reduces the container size by one, which is destroyed.
	// Relocates all the elements after the element erased to their new positions.
	iterator erase(const_iterator where)
	{
		if (where >= myData.myFirst && where < myData.myLast)
		{
			for (size_t i = (where - myData.myFirst) + 1; i < size(); i++) //(where - myFirst) == �}�C�W���R������m�Ai == �q�Ӧ�m���U�@��}�l
			{
				myData.myFirst[i - 1] = myData.myFirst[i]; //�N���᪺�ȥ������e��1��
			}
			myData.myLast--; //�]�R��1��A�GmyLast����e��1��(�����e1�檺�a�})
			return iterator(where);
		}
		else
			return nullptr;
	}

	// Removes all elements from the vector (which are destroyed),
	// leaving the container with a size of 0.
	// A reallocation is not guaranteed to happen,
	// and the vector capacity is not guaranteed to change due to calling this function.
	void clear()
	{
		myData.myLast = myData.myFirst;
	}

	// Returns an iterator pointing to the first element in the vector.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return myData.myFirst;
	}

	// Returns an iterator pointing to the first element in the vector.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myFirst);
	}

	// Returns an iterator referring to the past-the-end element in the vector container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as vector::begin.
	iterator end()
	{
		return myData.myLast;
	}

	// Returns an iterator referring to the past-the-end element in the vector container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as vector::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myLast);
	}

	// Returns a const_iterator pointing to the first element in the container.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	const_iterator cbegin() const
	{
		return begin();
	}

	// Returns a const_iterator pointing to the past-the-end element in the container.
	// If the container is empty, this function returns the same as vector::cbegin.
	// The value returned shall not be dereferenced.
	const_iterator cend() const
	{
		return end();
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

	// Returns a reference to the element at position "pos" in the vector container.
	value_type& operator[](const size_type pos)
	{
		if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
		{
			cout << "vector subscript out of range\n";
			exit(1);
		}

		return myData.myFirst[pos];
	}

	// Returns a reference to the element at position "pos" in the vector container.
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
	// Calling this function on an empty container causes undefined behavior.
	value_type& front()
	{
		return *myData.myFirst;
	}

	// Returns a reference to the first element in the vector.
	// Calling this function on an empty container causes undefined behavior.
	const value_type& front() const
	{
		return *myData.myFirst;
	}

	// Returns a reference to the last element in the vector.
	// Calling this function on an empty container causes undefined behavior.
	value_type& back()
	{
		return myData.myLast[-1];
	}

	// Returns a reference to the last element in the vector.
	// Calling this function on an empty container causes undefined behavior.
	const value_type& back() const
	{
		return myData.myLast[-1];
	}

private:
	ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const vector< Ty >& left, const vector< Ty >& right)
{
	if (left.size() != right.size())
	{
		return false;
	}

	//�]left�Mright���Oconst�A�G�]leftPtr�MrightPtr���Oconst_iterator
	for (typename vector<Ty>::const_iterator leftPtr = left.end() - 1, rightPtr = right.end() - 1; leftPtr != left.begin() - 1; leftPtr--, rightPtr--)
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