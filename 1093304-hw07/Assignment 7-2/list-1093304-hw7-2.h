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
		//建立一新的node並初始化
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		//(right.myData.myHead->next) == right第一個node的地址，在2者size相同之前，每次rightPtr紀錄下一個node的地址
		for (nodePtr rightPtr = right.myData.myHead->next; size() != right.size(); rightPtr = rightPtr->next)
		{
			insert(end(), rightPtr->myVal); //每次將right當前的值加入當前串列的最尾端
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
				thisPtr->myVal = rightPtr->myVal; //在2種Ptr都還未指完各自list上的每個node之前，每次將right內的值給this
			}

			if (size() < right.size()) //若right的size比較大
			{
				for (; size() != right.size(); rightPtr = rightPtr->next) //在2串列的size相同之前
				{
					insert(end(), rightPtr->myVal); //this需增加新的node來放入right內的值
				}
			}
			else if (size() > right.size()) //反之若this的size比較大
			{
				while (size() != right.size()) //在2串列的size相同之前
				{
					erase(end()->prev); //每次從最後一個node開始刪除
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
		newNode->prev = where->prev; //newNode的prev指向where的前一node(where->prev)
		newNode->next = where->prev->next; //newNode的next指向where(where->prev->next == 前一node的next == where的地址)
		newNode->prev->next = newNode->next->prev = newNode; //將newNode前後的node都指向自己(紀錄newNode的地址)
		myData.mySize++; //因插入一新node，故size + 1

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

		where->next->prev = where->prev; //(where後面的node)->prev改指where前面的node
		where->prev->next = where->next; //(where前面的node)->next改指where後面的node
		delete where; //釋放指定刪除的node
		myData.mySize--; //因刪除一node，故size - 1
	}

	// Removes all elements from the list container (which are destroyed),
	// and leaving the container with a size of 0.
	void clear() // erase all
	{
		while (myData.mySize != 0) // the list is not empty
		{
			erase(myData.myHead->next); //一直刪除node直到size == 0
		}
	}

private:
	ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const list< Ty >& left, const list< Ty >& right)
{
	if (left.size() != right.size()) //若2者的size不同，則2串列必不相等
	{
		return false;
	}

	typename	list<Ty>::const_iterator leftPtr = left.begin(); //用來記錄left當前的node
	typename	list<Ty>::const_iterator rightPtr = right.begin(); //用來記錄right當前的node
	for (; leftPtr != left.end(); leftPtr = leftPtr->next, rightPtr = rightPtr->next) //在2串列檢查完之前
	{
		if (leftPtr->myVal != rightPtr->myVal) //若2串列中的某一node不相等
		{
			return false;
		}
	}

	return true; //能做到此代表2串列相等
}

template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
	return !(left == right);
}

#endif // LIST