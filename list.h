#ifndef LIST_H
#define LIST_H
#include <stddef.h>

template <typename Type>
class list
{
	class Node;
	Node *head_, *tail_;
	unsigned int size_;
public:
	class iterator;
	
	list() : head_(NULL), tail_(NULL), size_(0)
	{	
	}
	explicit list(unsigned int size) : size_(size)
	{
		tail_ = head_ = (size)? new Node : NULL;
		for(int i = 1 ; i < size ; ++i)
		{
				tail_ = (tail_->next_ = new Node(tail_, Type()));
		}
	}
	list(unsigned int size, const Type &val) : size_(size)
	{
		tail_ = head_ = (size > 0)? new Node(NULL, val) : NULL;
		for(int i = 1 ; i < size ; ++i)
		{
				tail_ = (tail_->next_ = new Node(tail_, val));
		}
	}
	template <typename InputIterator>
	list(InputIterator first, InputIterator last)
		: head_(NULL), tail_(NULL), size_(0)
	{
		while (first != last)
		{
			push_back(*first++);
		}
	}
	list(const list &l) : tail_(NULL), head_(NULL), size_(l.size_)
	{
		if(l.empty()) return;
		tail_ = head_ = new Node(l.head_->obj_, NULL);
		Node *curNode = l.head_->next_;
		while(curNode != NULL)
		{
			tail_ = (tail_->next_ = new Node(tail_,curNode->obj_));
			curNode = curNode->next_;
		}
	}
	list & operator= (const list &l)
	{
		if(&l == this) return *this;
		clear();
		size_ = l.size_;
		if(l.empty()) return *this;
		tail_ = head_ = new Node(l.head_->obj_, NULL);
		Node *curNode = l.head_->next_;
		while(curNode != NULL)
		{
			tail_ = (tail_->next_ = new Node(tail_,curNode->obj_));
			curNode = curNode->next_;
		}
		return *this;
	}
	void push_back(const Type &obj)
	{
		if(tail_ == NULL)
		{
			tail_ = new Node(tail_, obj);
			head_ = tail_;
		}
		else
		{
			tail_ = (tail_->next_ = new Node(tail_, obj));
		}
		++size_;
	}
	void pop_back()
	{
		Node *temp = tail_;
		tail_ = tail_->previous_;
		tail_->next_ = NULL;
		delete temp;
		if(tail_ == NULL) //if empty
		{
			head_ = NULL; 
		}
		--size_;
	}
	Type & back() const
	{
		return tail_->obj_;
	}
	void push_front(const Type &obj)
	{
		if (head_ == NULL)
		{
			head_ = new Node(obj, head_);
			tail_ = head_;
		}
		else
		{
			head_ = (head_->previous_ = new Node(obj, head_));
		}
		++size_;
	}
	void pop_front()
	{
		Node *temp = head_;
		head_ = head_->next_;
		head_->previous_ = NULL;
		delete temp;
		if (head_ == NULL) //if empty
		{
			tail_ = NULL;
		}
		--size_;
	}
	iterator erase(iterator pos)
	{
		Node *erasing = pos.ptr_;
		++pos;
		if (erasing->previous_) //previous is not nulll
			erasing->previous_->next_ = erasing->next_;
		else //means pos is head
			head_ = erasing->next_;
		if (erasing->next_)
			erasing->next_->previous_ = erasing->previous_;
		else //means erasing is tail
			tail_ = erasing->previous_;
		delete erasing;
		--size_;
		return pos;
	}
	void erase(const iterator &lhs, const iterator &rhs)
	{
		Node *beg = lhs.ptr_, *end = rhs.ptr_;
		if (end)
		{
			end->previous_ = beg->previous_;
		}
		if (beg->previous_)
		{
			beg->previous_->next_ = end;
			end->previous_ = beg->previous_;
		}
		else
		{
			head_ = end;
		}
		while (beg != end)
		{
			Node *temp = beg;
			beg = beg->next_;
			delete temp;
		}
	}
	Type & front() const
	{
		return head_->obj_;
	}
	bool empty() const
	{
		return head_ == NULL;
	}
	unsigned int size() const
	{
		return size_;
	}
	iterator begin() const
	{
		return iterator(head_);
	}
	const iterator end() const
	{
		return iterator(NULL);
	}
	void clear()
	{
		size_ = 0;
		while(head_ != NULL)
		{
			Node *temp = head_;
			head_ = head_->next_;
			delete temp;
		}
		tail_ = NULL;
	}
	~list()
	{
		while(head_ != NULL)
		{
			Node *temp = head_;
			head_ = head_->next_;
			delete temp;
		}
	}
	
	
	class iterator
	{
		friend list;
	public:
		iterator() : ptr_(NULL)
		{
		}
		Type& operator* () const
		{
			return ptr_->obj_;
		}
		Type* operator-> () const
		{
			return &(ptr_->obj_);
		}
		iterator & operator++ ()
		{
			ptr_ = ptr_->next_;
			return *this;
		}
		iterator & operator-- ()
		{
			ptr_ = ptr_->previous_;
			return *this;
		}
		const iterator operator-- (int)
		{
			iterator copy = *this;
			ptr_ = ptr_->previous_;
			return copy;
		}
		const iterator operator++ (int)
		{
			iterator copy = *this;
			ptr_ = ptr_->next_;
			return copy;
		}
		bool operator != (const iterator &it) const
		{
			return it.ptr_ != ptr_;
		}
	private:
		iterator(Node *ptr) : ptr_(ptr)
		{
		}
		Node *ptr_;
	};
	
private:
	struct Node
	{
		friend iterator;
		friend list;
		Node(const Type &obj, Node *nextNode)
			: obj_(obj), next_(nextNode), previous_(NULL)
		{
		}
		Node(Node *prevNode, const Type &obj)
			: obj_(obj), next_(NULL), previous_(prevNode)
		{
		}
		Node() : next_(NULL), previous_(NULL)
		{
		}
	private:
		Node *next_, *previous_;
		Type obj_;
	};
	unsigned int calcSize() const
	{
		Node* temp = head_;
		unsigned int result = (head_ == NULL)? 0 : 1;
		while(temp != tail_)
		{
			++result;
			temp = temp->next_;
		}
		return result;
	}
};
#endif /* LIST_H */