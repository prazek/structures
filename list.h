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
	
	iterator begin() const
	{
		return iterator(head_);
	}
	iterator end() const
	{
		return iterator(NULL);
	}
	
	
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