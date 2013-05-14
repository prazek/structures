#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <vector>
#include <algorithm>

template <
	typename Object, 
	class Compare = std::less<Object> 
	>
class heap
{
	std::vector<Object> vec_;
	Compare compare_;
public:
	explicit heap(unsigned int size = 0) : vec_(1)
	{
		vec_.reserve(size + 1);	
	}
	explicit heap(const Compare &compare)	:
		compare_(compare),
		vec_(1)
	{
	}
	const Object & top() const
	{
		return vec_[1];
	}
	void push(const Object &object)
	{
		vec_.push_back(object);
		vec_[0] = min(vec_[0], object, compare_); //setting min guard
		int ind = vec_.size() - 1;
		while (compare_(vec_[ind], vec_[ind / 2])) //vec_[ind] < vec[ind/2] 
		{
			std::swap(vec_[ind], vec_[ind/2]);
			ind /= 2;
		}
	}
	void pop()
	{
		vec_[1] = vec_.back();
		vec_.pop_back();
		int ind = 1;
		int size = vec_.size();
		while(ind < size)
		{
			int low;
			if(ind*2 <= size && compare_(vec_[ind*2],vec_[ind]))
				low = ind*2;
			else
				low = ind;
			if(ind*2+1 <= size && compare_(vec_[ind*2+1],vec_[low]))
				low = ind*2|1;
			if(low == ind) 
				return;
			std::swap(vec_[ind], vec_[low]);
			ind = low;
		}
	}
	unsigned int size() const
	{
		return vec_.size() - 1;
	}
	bool empty() const
	{
		return vec_.size() <= 1;
	}
	void clear()
	{
		vec_.clear();
		vec_.push_back(Object());
	}
};

#endif /* HEAP_H */