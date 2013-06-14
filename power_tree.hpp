#ifndef POWER_TREE_HPP
#define POWER_TREE_HPP

#include <cstddef>
#include <algorithm>
template <typename T>
class power_tree
{
	T *tree_;
	size_t size_;
public:
	explicit power_tree(size_t size = 0, const T &val = T())
		: tree_(size ? new T[size+1] : 0),
		size_(size)
	{
	}
	
	template <typename T2>
	explicit power_tree(const power_tree<T2> &p)
		: tree_(new T[p.size_]),
		size_(p.size_)
	{
		copyValues(p.tree_);
	}
	
	void resize(size_t size);
	
	template <typename T2>
	power_tree & operator= (const power_tree<T2> &p)
	{
		if(*this == &p)
			return;
		
		delete[] tree_;
		size_ = p.size_;
		tree_ = new T[size_];
		
		copyValues(p.tree_);
		return *this;
	}
	T query(size_t index) const
	{
		++index;
		T result = T();
		for(; index > 0 ; index -= (index&-index)) //magic trick to get the biggest 
			// power of 2 which divide index
		{
			result += tree_[index];
		}
		return result;
	}
	
	T query(size_t lhs, size_t rhs) const
	{
		return query(rhs) - query(lhs-1);
	}
	
	void insert(size_t index, const T& val)
	{
		index++;
		for(; index < size_ ; index += (index & -index))
		{
			tree_[index] += val;
		}
	}
	
	size_t size() const
	{
		return size_;
	}
	
	void swap(power_tree &p)
	{
		std::swap(tree_, p.tree_);
		std::swap(size_,p.size_);
	}
	
	~power_tree()
	{
		delete[] tree_;
	}
	
private:
	void copyVaules(T *ptr)
	{
		T *iterator = &tree_, copyIterator = &ptr;
		while(iterator)
		{
			*iterator++ = *copyIterator++;
		}
	}
	
};

namespace std{
	

template <typename T>
void swap(power_tree<T> &a, power_tree<T> &b)
{
	a.swap(b);
}
}

#endif //POWER_TREE_HPP