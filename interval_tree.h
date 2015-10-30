#pragma once

#include <vector>
#include <cstddef>
#include <iterator>
template <
	typename Object,
	typename Query,
	class Alloc = std::allocator<Object>
>
class interval_tree 
{
	size_t size_;
	std::vector<Object, Alloc> vec_;
	Query query_;
	class interElement;
	friend interElement;
public:
	
	typedef Object value_type;
	typedef Alloc allocator_type;
	
	explicit interval_tree(size_t size = 0, const Object &val = Object()) :
		size_(calc(size)),
		vec_(size_ * 2, val)
	{
		build();
	}
	
	template <typename InputIterator>
	interval_tree(InputIterator first, InputIterator last, typename
			std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0) 
		: size_(calc(std::distance(first,last))),
		vec_(size_ * 2)
	{
		typename std::vector<Object>::iterator it = vec_.begin() + size_;
		for(; first != last ;)
		{
			*it++ = *first++;
		}
		build();
	}
	interElement & operator[] (size_t index)
	{
		element_.index_ = index + size_;
		element_.ptr_ = this;
		return element_;
	}
	const Object & operator[] (size_t index) const
	{
		return vec_.at(index + size_);
	}
	const Object & query() const
	{
		return vec_[1];
	}
	Object rquery(size_t rhs) const
	{
		return query(0, rhs);
	}
	Object lquery(size_t lhs) const
	{
		return query(lhs, size());
	}
	Object query(size_t lhs, size_t rhs) const
	{
		lhs += size_;
		rhs += size_;
		Object result = vec_.at(lhs);
		if (lhs != rhs)
			result = query_(result, vec_.at(rhs));
		
		while ((lhs / 2) != (rhs / 2))
		{
			if (lhs % 2 == 0)
				result = query_(result, vec_[lhs + 1]);
			if (rhs % 2 == 1)
				result = query_(result, vec_[rhs - 1]);
			lhs /= 2;
			rhs /= 2;
		}
		return result;
	}
	template <class Functor>
	int find(const Functor &functor) const
	{
		int ind = 1;
		while (ind < size_)
		{
			ind = functor(vec_[ind*2], vec_[ind*2|1]) ? ind*2 : ind*2|1;
		}
		return ind - size_;
	}
	void resize(size_t size)
	{
		size_t oldsize = size_;
		size_ = calc(size);
		if(size_ == oldsize) 
			return;
		std::vector<Object> newVec(size_ * 2);
		size_t end = size_ + std::min(oldsize, size_);
		for(int i = size_, j = oldsize ; i < end ; ++i)
		{
			newVec[i] = vec_[j++];
		}
		vec_ = newVec;
		build();
	}
	/*
	 * Function to set values of leafs
	 * t.serValues(x) is equal to t = interval_tree(t.size(), x)
	 */
	void set_values(const Object &val)
	{
		typename std::vector<Object, Alloc>::iterator it = vec_.begin() + size_;
		for(; it != vec_.end() ; ++it)
		{
			*it = val;
		}
		build();
	}
	/*
	 * Equal to resize(0)
	 */
	void clear()
	{
		vec_.resize(0);
		size_ = 0;
	}
	size_t size() const
	{
		return size_;
	}
	void swap(interval_tree &tree)
	{
		vec_.swap(tree.vec_);
		std::swap(size_, tree.size_);
	}
	
	class iterator : 
			public std::vector<Object, Alloc>::const_iterator
	{
		typedef typename std::vector<Object, Alloc>::const_iterator 	super;
	public:
		iterator()
		{
		}
		friend interval_tree;
		iterator(const super & it)
			: super(it)
		{
		}
	};
	
	iterator begin() const
	{
		return iterator(vec_.begin() + size_);
	}
	iterator end() const
	{
		return iterator(vec_.end());
	}
private:
	/*
	 * Function sets valid values to the rest of the tree, based on
	 * values in the leafs 
	 */
	void build()
	{
		for (int i = size_ - 1; i > 0 ; --i)
		{
			vec_[i] = query_(vec_[i*2], vec_[i*2 + 1]);
		}
	}
	/*
	 * Function to calculate size of tree used to make full binary tree.
	 * Returns first bigger or equal power of 2 than p.
	 */
	int calc(unsigned int p)
	{
		if (p == 0)
			return 0;
		int res = 1;
		while (res <= p){
			res *= 2;
		}
		return res;
	}
	void insert(size_t index)
	{
		index /= 2;
		while (index != 1)
		{
			vec_[index] = query_(vec_[index * 2], vec_[index * 2 + 1]);
			index /= 2;
		}
	}
	
	class interElement
	{
		friend interval_tree;
		size_t index_;
		interval_tree<Object, Query, Alloc> *ptr_;
		interElement(interval_tree *ref) : ptr_(ref)
		{
		}
	public:
		interElement() {}
		#define OPERATOR(OP)\
		const Object & operator OP (const Object &val){\
			ptr_->vec_.at(index_) OP val;\
			ptr_->insert(index_);\
			return ptr_->vec_[index_];\
		}
		
		OPERATOR(=)
		OPERATOR(+=)
		OPERATOR(-=)
		OPERATOR(*=)
		OPERATOR(%=)
		OPERATOR(/=)
		OPERATOR(|=)
		OPERATOR(&=)
		OPERATOR(^=)
		OPERATOR(>>=)
		OPERATOR(<<=)
		#undef OPERATOR
		operator const Object& () const
		{
			return ptr_->vec_.at(index_);
		}
	};
	static interElement element_;
};

template <typename Object,typename Query,class Alloc>
typename interval_tree<Object, Query, Alloc>::interElement 
interval_tree<Object, Query, Alloc>::element_;

