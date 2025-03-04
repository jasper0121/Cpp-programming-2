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
	myFirst = new int[count](); //myFirst�إ߰ʺA�}�C�A�ñN�C��}�C����ƪ�l�Ƭ�0
	myLast = myEnd = myFirst + count; //myLast == myEnd == myFirst + �`�Ŷ���
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector(const vector& right) //STL vector�ƻs�}�C�ɥu�ƻs������������
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
vector::iterator vector::insert(const_iterator where, const value_type& val) //const_iterator == const int*
{
	if (myFirst == nullptr) //�YmyFirst�٥��إ߰ʺA�}�C
	{
		myFirst = new int[1]; //�h�t�m�ʺA�}�C(1��)
		myFirst[0] = val;
		myLast = myEnd = myFirst + 1; //myLast == myEnd == myFirst + 1
	}
	else
	{
		if (size() == 1 && capacity() == 1) //�Y�Ŷ��u��1��B�Ӯ椺������
		{
			pointer temp = myFirst; //�ŧi�Ȧs�ë��VmyFirst�}�C(pointer == int*)
			myFirst = new int[2]; //���s�t�m(2��)
			if (temp == where) //�Y�°}�C(�Ȧs)������a�} == �������w�[�J���a�}
			{
				myFirst[0] = val; //�h�N�s�����[�J0���}�C
				myFirst[1] = temp[0];
			}
			else
			{
				myFirst[0] = temp[0];
				myFirst[1] = val; //�_�h�N�s�����[�J1���}�C
			}
			myLast = myEnd = myFirst + 2; //myLast == myEnd == myFirst + 2
			delete[]temp; //����Ȧs���O����
		}
		else if (size() == capacity()) //�Y�C�ӪŶ���������(�S���Ŷ���J�s����)
		{
			pointer temp = myFirst; //�ŧi�Ȧs�ë��VmyFirst�}�C
			size_t old_length = capacity(); //�������J�e�°}�C�`����
			size_t new_length = old_length * 3 / 2; //�`���� >= 2�ɡA�s�ʺA�}�C���� == �ª��� * 1.5��
			myFirst = new int[new_length]; //���s�t�m
			for (size_t a = 0, b = 0; a < old_length + 1; a++, b++) //a == myFirst��e�}�C�s���Ab == temp��e�}�C�s���Aold_length + 1 == �s�����`����
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
		else if (size() < capacity()) //�Y�٦��Ŷ��i�H��J�s����
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
	}
	return myFirst;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign(const vector& right)
{
	size_t rightSize = right.myLast - right.myFirst; //right������������

	if (capacity() >= rightSize) //�Y�������Ŷ��i�Hassign
	{
		for (size_t a = 0; a < rightSize; a++) //�h�Nright���������ƻs����e�}�C
		{
			myFirst[a] = right.myFirst[a];
		}
	}
	else if (capacity() < rightSize && rightSize <= capacity() * 3 / 2) //�Y��e�Ŷ������Hassign�A���X�i�Ŷ���h�i�H��
	{
		size_t new_length = capacity() * 3 / 2; //�s�ʺA�}�C�Ŷ��� == �ªŶ���*1.5��
		delete[]myFirst; //�����°}�C
		myFirst = new int[new_length]; //���s�t�m
		for (size_t b = 0; b < rightSize; b++) //�Nright���������ƻs����e�}�C
		{
			myFirst[b] = right.myFirst[b];
		}
		myEnd = myFirst + new_length; //myEnd == myFirst + �`�Ŷ���
	}
	else if (rightSize > capacity() * 3 / 2) //�Y�X�i�Ŷ��ᤴ�����Hassign
	{
		delete[]myFirst; //�����°}�C
		myFirst = new int[rightSize]; //���s�t�m(�Ŷ���right�������Ӽ�)
		for (size_t c = 0; c < rightSize; c++) //�Nright���������ƻs����e�}�C
		{
			myFirst[c] = right.myFirst[c];
		}
		myEnd = myFirst + rightSize; //myEnd == myFirst + right����������
	}
	myLast = myFirst + rightSize; //myLast == myFirst + right����������
	return *this; //�^�Ƿ�e������
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase(const_iterator where)
{
	for (int a = 0; a < size(); a++)
	{
		if (myFirst + a == where) //�YmyFirst�}�C�W�Y��m == ���w�R�����a�}
		{
			for (int b = a + 1; b < size(); b++) //�h�q�U1��}�l
			{
				myFirst[b - 1] = myFirst[b]; //�N���᪺�ȥ������e��1��
			}
			break; //�R�������A���X�j��
		}
	}
	myLast--; //�]�R��1��A�GmyLast����e��1��(�����e1�檺�a�})
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