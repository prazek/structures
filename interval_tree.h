#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <vector>
template <
	typename Object,
	typename Insert,
	typename Query = Insert
>
class interval_tree 
{
	unsigned int size_;
	std::vector<Object> vec_;
	Insert insert_;
	Query query_;
public:
	explicit interval_tree(unsigned int size = 1) :
		size_(calc(size)),
		vec_(size_ * 2)
	{
	}
	explicit interval_tree(const std::vector<Object> &vec) :
		size_(calc(vec.size())),
		vec_(size_ * 2)
	{
		typename std::vector<Object>::const_iterator itcopy;
		typename std::vector<Object>::iterator it = vec_.begin() + size_;
		for(itcopy = vec.begin(); itcopy != vec.end() ; ++itcopy)
		{
			*(it++) = *itcopy;
		}
		build();
	}
	Object operator[] (unsigned int index)
	{
		return vec_[index + size_];
	}
	void insert(int index, Object val)
	{
		index += size_;
		vec_[index] = insert_(vec_.at(index), val);
		index /= 2;
		while (index != 1)
		{
			vec_[index] = query_(vec_[index*2], vec_[index*2+1]);
			index /= 2;
		}
	}
	Object query(int lhs = 0) const
	{
		return query(lhs, size_);
	}
	Object query(int lhs, int rhs) const
	{
		lhs += size_;
		rhs += size_;
		Object result = vec_.at(lhs);
		if (lhs != rhs)
			result = query_(result, vec_.at(rhs));
		
		while ((lhs >> 1) != (rhs >> 1))
		{
			if (!(lhs & 1))
				result = query_(result, vec_[lhs + 1]);
			if (rhs & 1) 
				result = query_(result, vec_[rhs - 1]);
			lhs >>= 1;
			rhs >>= 1;
		}
		return result;
	}
	
private:
	void build()
	{
		for (int i = size_ - 1; i > 0 ; --i)
		{
			vec_[i] = query_(vec_[i*2], vec_[i*2 + 1]);
		}
	}
	int calc(unsigned int p)
	{ 
		// function to calculate size of tree
		int res = 1;
		while (res <= p){
			res <<= 1;
		}
		return res;
	}
};

#endif /* INTERVAL_TREE_H */