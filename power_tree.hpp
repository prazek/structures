#ifndef POWER_TREE_HPP
#define POWER_TREE_HPP

#include <cstring>
#include <cstddef>
#include <algorithm>

template <typename T>
class power_tree
{
	T *tree_;
	size_t size_;
public:
	explicit power_tree(size_t size = 0)
		: tree_(size ? new T[size+1] : 0),
		size_(size+1)
	{
	}
	
	power_tree(const power_tree &p)
		: tree_(new T[p.size_]),
		size_(p.size_)
	{
		memcpy(tree_, p.tree_, size_ * sizeof(T));
	}
	
	void resize(size_t size)
	{
		if(++size != size_)
		{
			T* temp = new T[size];
			size_ = size;
			memcpy(temp, tree_, size * sizeof(T));
			delete[] tree_;
			tree_ = temp;
		}
	}
	
	power_tree & operator= (const power_tree &p)
	{
		if(this != &p)
		{
			delete[] tree_;
			size_ = p.size_;
			tree_ = new T[size_];
			memcpy(tree_, p.tree_, size_ * sizeof(T));
		}
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
		for(; index < size_ ; index += (index & -index)) // using magic
		{
			tree_[index] += val;
		}
	}
	
	size_t size() const
	{
		return size_-1;
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
	
};

namespace std
{
	template <typename T>
	void swap(power_tree<T> &a, power_tree<T> &b)
	{
		a.swap(b);
	}
}

#endif //POWER_TREE_HPP