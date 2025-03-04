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
	myFirst = new int[count](); //myFirst�إ߰ʺA�}�C�A�ñN�C��}�C����ƪ�l�Ƭ�0
	myLast = myEnd = myFirst + count; //myLast == myEnd == myFirst + �`�Ŷ���
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector& right)
{
	size_type rightSize = right.myLast - right.myFirst; //right���������Ӽ�
	myFirst = new int[rightSize]; //�إ߷s�ʺA�}�C�A���`��Ƭ�right�������Ӽ�
	myLast = myEnd = myFirst + rightSize; //�]STL vector�u�ƻs�������������A�GmyLast == myEnd
	for (size_type n = 0; n < rightSize; n++)
	{
		myFirst[n] = right.myFirst[n]; //�ƻs�}�C������
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
	if (size() == capacity()) //�Y�C�ӪŶ���������(�S���Ŷ���J�s����)
	{
		pointer temp = myFirst; //�ŧi�Ȧs�ë��VmyFirst�}�C
		int old_length = capacity(); //�������J�e�°}�C�`����
		int new_length = (capacity() <= 1) ? old_length + 1 : old_length * 3 / 2; //�`���� <= 1�ɡA�s�ʺA�}�C���� == �ª��� + 1�A�Ϥ� == �ª��� * 1.5��
		myFirst = new int[new_length]; //���s�t�m
		for (int a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst��e�}�C�s���Ab == temp��e�}�C�s���Aold_length + 1 == �s�����`����
		{
			if (temp + a == where) //�Ytemp�}�C�W�Y��m == ���w���J���a�}
			{
				myFirst[a] = val; //�h�N�s�����[�J�Ӯ�}�C
				b--; //����temp[b]���ȥ��ƻs�A�Yb����1�h�ӭȤ��|�Q�s�JmyFirst[a]��
				continue;
			}
			myFirst[a] = temp[b]; //�Ntemp���������ƻs����e�}�C
		}
		myLast = myFirst + old_length + 1; //myLast == myFirst + �°}�C�`����+���J1�s����
		myEnd = myFirst + new_length; //myEnd == myFirst + �s�}�C�`����
		delete[]temp; //����Ȧs���O����
	}
	else //�Y�٦��Ŷ��i�H��J�s����(�Ysize() < capacity())
	{
		for (int c = size(); c >= 0; c--) //�]�|��1�s�����[�J�A�G�@�}�lc == size()�ӫDsize() - 1
		{
			if (myFirst + c == where) //�YmyFirst�}�C�W�Y��m == ���w���J���a�}
			{
				myFirst[c] = val; //�N�s�����[�J�Ӯ�}�C
				myLast++; //�]���J1��A�GmyLast����᭱1��(������1�檺�a�})
				break; //���J�����A���X�j��
			}
			myFirst[c] = myFirst[c - 1]; //�q�̫�@�Ӥ����}�l�A�C���N�Ӥ������Ჾ1��
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
		size_t rightSize = right.myLast - right.myFirst; //right���������Ӽ�
		if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //�Y��e�Ŷ������Hassign�A���X�i�Ŷ���h�i�H��
		{
			size_t new_length = capacity() * 3 / 2; //�s�ʺA�}�C�Ŷ��� == �ªŶ���*1.5��
			delete[]myFirst; //�����°}�C
			myFirst = new int[new_length]; //���s�t�m
			myEnd = myFirst + new_length; //myEnd == myFirst + �`�Ŷ���
		}
		else if (rightSize > capacity() * 3 / 2) //�Y�X�i�Ŷ��ᤴ�����Hassign
		{
			delete[]myFirst; //�����°}�C
			myFirst = new int[rightSize]; //���s�t�m(�Ŷ���right�������Ӽ�)
			myEnd = myFirst + rightSize; //myEnd == myFirst + right����������
		}

		for (size_t i = 0; i < rightSize; i++) //�Nright���������ƻs����e�}�C
		{
			myFirst[i] = right.myFirst[i];
		}
		myLast = myFirst + rightSize; //myLast == myFirst + right����������
	}

	return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where)
{
	for (size_t i = (where - myFirst) + 1; i < size(); i++) //(where - myFirst) == �}�C�W���R������m�Ai == �q�Ӧ�m���U�@��}�l
	{
		myFirst[i - 1] = myFirst[i]; //�N���᪺�ȥ������e��1��
	}
	myLast--; //�]�R��1��A�GmyLast����e��1��(�����e1�檺�a�})
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