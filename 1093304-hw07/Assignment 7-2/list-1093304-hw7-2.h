// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
	ListNode* next;  // successor node, or first element if head
	ListNode* prev;  // predecessor node, or last element if head
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

	using iterator = node*;
	using const_iterator = const node*;

	// empty container constructor (default constructor)
	// Constructs an empty container, with no elements.
	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	// fill constructor
	// Constructs a container with "count" elements.
	// Each element is initialized as 0.
	list(size_type count) // construct list from count * Ty()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				insert(end(), Ty());
	}

	// copy constructor
	// Constructs a container with a copy of each of the elements in "right",
	// in the same order.
	list(const list& right)
		: myData()
	{
		//�إߤ@�s��node�ê�l��
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		//(right.myData.myHead->next) == right�Ĥ@��node���a�}�A�b2��size�ۦP���e�A�C��rightPtr�����U�@��node���a�}
		for (nodePtr rightPtr = right.myData.myHead->next; size() != right.size(); rightPtr = rightPtr->next)
		{
			insert(end(), rightPtr->myVal); //�C���Nright��e���ȥ[�J��e��C���̧���
		}
	}

	// List destructor
	// Destroys the container object.
	// Deallocates all the storage capacity allocated by the list container.
	~list()
	{
		clear();
		delete myData.myHead;
	}

	// Assigns new contents to the container, replacing its current contents,
	// and modifying its size accordingly.
	// Copies all the elements from "right" into the container
	// (with "right" preserving its contents).
	list& operator=(const list& right)
	{
		if (this != &right)
		{
			nodePtr rightPtr = right.myData.myHead->next;
			for (nodePtr thisPtr = myData.myHead->next; thisPtr != end() && rightPtr != right.end(); thisPtr = thisPtr->next, rightPtr = rightPtr->next)
			{
				thisPtr->myVal = rightPtr->myVal; //�b2��Ptr���٥������U��list�W���C��node���e�A�C���Nright�����ȵ�this
			}

			if (size() < right.size()) //�Yright��size����j
			{
				for (; size() != right.size(); rightPtr = rightPtr->next) //�b2��C��size�ۦP���e
				{
					insert(end(), rightPtr->myVal); //this�ݼW�[�s��node�ө�Jright������
				}
			}
			else if (size() > right.size()) //�Ϥ��Ythis��size����j
			{
				while (size() != right.size()) //�b2��C��size�ۦP���e
				{
					erase(end()->prev); //�C���q�̫�@��node�}�l�R��
				}
			}
		}

		return *this;
	}

	// Returns an iterator pointing to the first element in the list container.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return iterator(myData.myHead->next);
	}

	// Returns an iterator pointing to the first element in the list container.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myHead->next);
	}

	// Returns an iterator referring to the past-the-end element in the list container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list container.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as list::begin.
	iterator end()
	{
		return iterator(myData.myHead);
	}

	// Returns an iterator referring to the past-the-end element in the list container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list container.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as list::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myHead);
	}

	// Returns the number of elements in the list container.
	size_type size() const
	{
		return myData.mySize;
	}

	// Returns whether the list container is empty (i.e. whether its size is 0).
	bool empty() const
	{
		return myData.mySize == 0;
	}

	// Returns a reference to the first element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	reference front()
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the first element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	const_reference front() const
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the last element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	// Returns a reference to the last element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	const_reference back() const
	{
		return myData.myHead->prev->myVal;
	}

	// The container is extended by inserting a new element
	// before the element at the specified position.
	// This effectively increases the list size by the amount of elements inserted.
	// Returns an iterator that points to the newly inserted element.
	iterator insert(const_iterator where, const Ty& val) // insert val at where
	{
		nodePtr newNode = new node;
		newNode->myVal = val;
		newNode->prev = where->prev; //newNode��prev���Vwhere���e�@node(where->prev)
		newNode->next = where->prev->next; //newNode��next���Vwhere(where->prev->next == �e�@node��next == where���a�})
		newNode->prev->next = newNode->next->prev = newNode; //�NnewNode�e�᪺node�����V�ۤv(����newNode���a�})
		myData.mySize++; //�]���J�@�snode�A�Gsize + 1

		return iterator(newNode);
	}

	// Removes from the list container the element at the specified position.
	// This effectively reduces the container size one, which is destroyed.
	// Returns an iterator pointing to the element that followed the element erased.
	// This is the container end if the operation erased the last element in the sequence.
	iterator erase(const_iterator where)
	{
		if (myData.mySize == 0)
		{
			return myData.myHead;
		}

		where->next->prev = where->prev; //(where�᭱��node)->prev���where�e����node
		where->prev->next = where->next; //(where�e����node)->next���where�᭱��node
		delete where; //������w�R����node
		myData.mySize--; //�]�R���@node�A�Gsize - 1
	}

	// Removes all elements from the list container (which are destroyed),
	// and leaving the container with a size of 0.
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

	typename	list<Ty>::const_iterator leftPtr = left.begin(); //�ΨӰO��left��e��node
	typename	list<Ty>::const_iterator rightPtr = right.begin(); //�ΨӰO��right��e��node
	for (; leftPtr != left.end(); leftPtr = leftPtr->next, rightPtr = rightPtr->next) //�b2��C�ˬd�����e
	{
		if (leftPtr->myVal != rightPtr->myVal) //�Y2��C�����Y�@node���۵�
		{
			return false;
		}
	}

	return true; //�వ�즹�N��2��C�۵�
}

template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
	return !(left == right);
}

#endif // LIST