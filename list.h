#ifndef LIST_H
#define LIST_H
#include <stddef.h>

template <typename Type>
class list
{
	class Node;
public:
	class iterator;
	
	list() : head_(NULL), tail_(NULL)
	{	
	}
	explicit list(unsigned int size)
	{
		tail_ = head_ = (size)? new Node : NULL;
		for(int i = 1 ; i < size ; ++i)
		{
				tail_ = (tail_->next_ = new Node(tail_, Type()));
		}
	}
	explicit list(unsigned int size, const Type &val)
	{
		tail_ = head_ = (size > 0)? new Node(NULL, val) : NULL;
		for(int i = 1 ; i < size ; ++i)
		{
				tail_ = (tail_->next_ = new Node(tail_, val));
		}
	}
	list(const list &l) : tail_(NULL), head_(NULL)
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
	}
	void pop_back()
	{
		Node *temp = tail_;
		tail_ = tail_->previous_;
		delete temp;
		if(tail_ == NULL) //if empty
		{
			head_ = NULL; 
		}
	}
	Type & back() const
	{
		return tail_->obj_;
	}
	void push_front(const Type &obj)
	{
		if(head_ == NULL)
		{
			head_ = new Node(obj, head_);
			tail_ = head_;
		}
		else
		{
			head_ = (head_->previous_ = new Node(obj, head_));
		}
	}
	void pop_front()
	{
		Node *temp = head_;
		head_ = head_->next_;
		delete temp;
		if(head_ == NULL) //if empty
		{
			tail_ = NULL;
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
		Node* temp = head_;
		unsigned int result = (head_ == NULL)? 0 : 1;
		while(temp != tail_)
		{
			++result;
			temp = temp->next_;
		}
		return result;
	}
	iterator begin() const
	{
		return iterator(head_);
	}
	iterator end() const
	{
		return iterator(NULL);
	}
	void clear()
	{
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
	Node *head_, *tail_;
};
#endif /* LIST_H */