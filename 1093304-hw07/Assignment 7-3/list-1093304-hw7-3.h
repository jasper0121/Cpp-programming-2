// list standard header

#ifndef LIST
#define LIST

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::const_pointer;
	using reference = const value_type&;

	ListConstIterator()
		: ptr()
	{
	}

	ListConstIterator(nodePtr pNode)
		: ptr(pNode)
	{
	}

	reference operator*() const
	{
		return ptr->myVal;
	}

	ListConstIterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	ListConstIterator operator++(int)
	{
		ListConstIterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	ListConstIterator& operator--()
	{
		ptr = ptr->prev;
		return *this;
	}

	ListConstIterator operator--(int)
	{
		ListConstIterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}

	bool operator==(const ListConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ListConstIterator& right) const
	{
		return !(*this == right);
	}

	nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator
{
public:
	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::const_pointer;
	using reference = value_type&;

	ListIterator()
		: ptr()
	{
	}

	ListIterator(nodePtr pNode)
		: ptr(pNode)
	{
	}

	reference operator*() const
	{
		return ptr->myVal;
	}

	ListIterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	ListIterator operator++(int)
	{
		ListIterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	ListIterator& operator--()
	{
		ptr = ptr->prev;
		return *this;
	}

	ListIterator operator--(int)
	{
		ListIterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}

	bool operator==(const ListIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ListIterator& right) const
	{
		return !(*this == right);
	}

	nodePtr ptr; // pointer to node
};

template< typename ValueType >
struct ListNode // list node
{
	using nodePtr = ListNode*;

	nodePtr next; // successor node, or first element if head
	nodePtr prev; // predecessor node, or last element if head
	ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
	using node = ListNode< Ty >;
	using nodePtr = node*;

	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	ListVal() // initialize data
		: myHead(),
		mySize(0)
	{
	}

	nodePtr myHead; // pointer to head node
	size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
	using node = ListNode< Ty >;
	using nodePtr = node*;
	using ScaryVal = ListVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = ListIterator< ScaryVal >;
	using const_iterator = ListConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	// empty list constructor (default constructor)
	// Constructs an empty list, with no elements.
	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	explicit list(size_type count) // construct list from count * Ty()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				insert(cend(), Ty());
	}

	list(const list& right)
		: myData()
	{
		//�إߤ@�s��node�ê�l��
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		for (const_iterator rightPtr = right.begin(); size() != right.size(); rightPtr++) //�]right��const�A�GrightPtr���]��const_iterator
		{
			insert(cend(), *rightPtr); //�C���Nright��e���ȥ[�J��e��C���̧���(insert�ǤJ���ȶ���const)
		}
	}

	// List destructor
	// Destroys the list object.
	// Deallocates all the storage capacity allocated by the list.
	~list()
	{
		clear();
		delete myData.myHead;
	}

	list& operator=(const list& right)
	{
		if (this != &right)
		{
			const_iterator rightPtr = right.begin();
			for (iterator thisPtr = begin(); thisPtr != end() && rightPtr != right.end(); thisPtr++, rightPtr++) //�b2��iterator���٥������U��list�W���C��node���e
			{
				*thisPtr = *rightPtr; //�C���Nright�����ȵ�this
			}

			if (size() < right.size()) //�Yright��size����j
			{
				for (; size() != right.size(); rightPtr++) //�b2��C��size�ۦP���e
				{
					insert(cend(), *rightPtr); //this�ݼW�[�s��node�ө�Jright������
				}
			}
			else if (size() > right.size()) //�Ϥ��Ythis��size����j
			{
				while (size() != right.size()) //�b2��C��size�ۦP���e
				{
					erase(cend().ptr->prev); //�C���q�̫�@��node�}�l�R��
				}
			}
		}

		return *this;
	}

	// Returns an iterator pointing to the first element in the list.
	// If the list is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return iterator(myData.myHead->next);
	}

	// Returns a const_iterator pointing to the first element in the list.
	// If the list is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myHead->next);
	}

	// Returns an iterator referring to the past-the-end element in the list.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the list is empty, this function returns the same as list::begin.
	iterator end()
	{
		return iterator(myData.myHead);
	}

	// Returns a const_iterator referring to the past-the-end element in the list.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the list is empty, this function returns the same as list::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myHead);
	}

	// Returns a reverse iterator pointing to the last element in the list
	// ( i.e., its reverse beginning ).
	// rbegin points to the element right before the one
	// that would be pointed to by member end.
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	// Returns a reverse iterator pointing to the last element in the list
	// ( i.e., its reverse beginning ).
	// rbegin points to the element right before the one
	// that would be pointed to by member end.
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	// Returns a reverse iterator pointing to the theoretical element
	// preceding the first element in the list
	// (which is considered its reverse end).
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	// Returns a reverse iterator pointing to the theoretical element
	// preceding the first element in the list
	// (which is considered its reverse end).
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// Returns a const_iterator pointing to the first element in the list.
	// If the list is empty, the returned iterator value shall not be dereferenced.
	const_iterator cbegin() const
	{
		return begin();
	}

	// Returns a const_iterator pointing to the past-the-end element in the list.
	// If the list is empty, this function returns the same as list::cbegin.
	// The value returned shall not be dereferenced.
	const_iterator cend() const
	{
		return end();
	}

	// Returns a const_reverse_iterator pointing to the last element in the list
	// (i.e., its reverse beginning).
	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}

	// Returns a const_reverse_iterator pointing to the theoretical element
	// preceding the first element in the list (which is considered its reverse end).
	const_reverse_iterator crend() const
	{
		return rend();
	}

	// Returns the number of elements in the list.
	size_type size() const
	{
		return myData.mySize;
	}

	// Returns whether the list is empty (i.e. whether its size is 0).
	bool empty() const
	{
		return myData.mySize == 0;
	}

	// Returns a reference to the first element in the list.
	// Calling this function on an empty list causes undefined behavior.
	reference front()
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the first element in the list.
	// Calling this function on an empty list causes undefined behavior.
	const_reference front() const
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the last element in the list.
	// Calling this function on an empty list causes undefined behavior.
	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	// Returns a reference to the last element in the list.
	// Calling this function on an empty list causes undefined behavior.
	const_reference back() const
	{
		return myData.myHead->prev->myVal;
	}

	// The list is extended by inserting a new element
	// before the element at the specified position.
	// This effectively increases the list size by the amount of elements inserted.
	iterator insert(const_iterator where, const Ty& val) // insert val at where
	{
		nodePtr newNode = new node;
		newNode->myVal = val;
		newNode->prev = where.ptr->prev; //newNode��prev���Vwhere.ptr���e�@node(where.ptr->prev)
		newNode->next = where.ptr->prev->next; //newNode��next���Vwhere.ptr(where.ptr->prev->next == �e�@node��next == where.ptr���a�})
		newNode->prev->next = newNode->next->prev = newNode; //�NnewNode�e�᪺node�����V�ۤv(����newNode���a�})
		myData.mySize++; //�]���J�@�snode�A�Gsize + 1

		return iterator(newNode);
	}

	// Removes from the list the element at the specified position.
	// This effectively reduces the list size one, which is destroyed.
	iterator erase(const_iterator where)
	{
		if (myData.mySize == 0)
		{
			return myData.myHead;
		}

		where.ptr->next->prev = where.ptr->prev; //(where.ptr�᭱��node)->prev���where.ptr�e����node
		where.ptr->prev->next = where.ptr->next; //(where.ptr�e����node)->next���where.ptr�᭱��node
		delete where.ptr; //������w�R����node
		myData.mySize--; //�]�R���@node�A�Gsize - 1
	}

	// Removes all elements from the list (which are destroyed),
	// and leaving the list with a size of 0.
	void clear() // erase all
	{
		while (myData.mySize != 0) // the list is not empty
		{
			erase(myData.myHead->next); //�@���R��node����size == 0
		}
	}

private:
	ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const list< Ty >& left, const list< Ty >& right)
{
	if (left.size() != right.size()) //�Y2�̪�size���P�A�h2��C�����۵�
	{
		return false;
	}

	//�]left�Mright���Oconst�A�G�]leftPtr�MrightPtr���Oconst_iterator�A���󤤪�left.end() == --left.begin()
	for (typename list<Ty>::const_iterator leftPtr = --left.end(), rightPtr = --right.end(); leftPtr != left.end(); leftPtr--, rightPtr--) //�b2��C�ˬd�����e
	{
		if (*leftPtr != *rightPtr) //�Y2��C�����Y�@node���۵�
		{
			return false;
		}
	}
	return true; //�వ�즹�N��2��C�۵�
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
	return !(left == right);
}

#endif // LIST
