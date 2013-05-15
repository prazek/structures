#ifndef FRACTION_H
#define FRACTION_H
#include <algorithm>
class fraction
{
	long long num_, denom_;
public:
	fraction(long long numerator = 0, long long denominator = 1)
		: num_(numerator), 
		denom_(denominator)
	{
		shorten();
	}
	
	operator double() const
	{
		return num_/denom_;
	}
	bool operator ==(const fraction &f) const
	{
		return num_ == f.num_ & denom_ == f.denom_;
	}
	bool operator!= (const fraction &f) const
	{
		return num_ != f.num_ | denom_ != f.denom_; 
	}
	#define OP(c) bool operator c (const fraction &f) const \
	{ \
		return denom_ * f.num_ c f.denom_ * num_;\
	}
	OP(<);
	OP(<=);
	OP(>);
	OP(>=);
	#undef OP
	const fraction operator+ (const fraction &f) const
	{
		return fraction(num_*f.denom_+f.num_*denom_, denom_*f.denom_);
	}
	const fraction operator- (const fraction &f) const
	{
		return fraction(num_*f.denom_-f.num_*denom_, denom_*f.denom_);
	}
	const fraction operator* (const fraction &f) const
	{
		return fraction(num_*f.num_, denom_*f.denom_);
	}
	const fraction operator/ (const fraction &f) const
	{
		return fraction(num_*f.denom_, denom_*f.num_);
	}
	const fraction & operator+= (const fraction &f)
	{
		num_ = num_*f.denom_+f.num_*denom_;
		denom_ *= f.denom_;
		shorten();
		return *this;
	}
	const fraction & operator-= (const fraction &f)
	{
		num_ = num_*f.denom_-f.num_*denom_;
		denom_ *= f.denom_;
		shorten();
		return *this;
	}
	const fraction & operator*= (const fraction &f)
	{
		num_ *= f.num_;
		denom_ *= f.denom_;
		shorten();
		return *this;
	}
	const fraction & operator/= (const fraction &f)
	{
		num_ *= f.denom_;
		denom_ *= f.num_;
		shorten();
		return *this;
	}
	const fraction & operator++()
	{
		num_ += denom_;
		shorten();
		return *this;
	}
	const fraction operator++(int)
	{
		num_ += denom_;
		shorten();
		return fraction(num_-denom_, denom_);
	}
	const fraction & operator--()
	{
		num_-= denom_;
		shorten();
		return *this;
	}
	const fraction operator--(int)
	{
		num_ -= denom_;
		shorten();
		return fraction(num_+denom_, denom_);
	}
private:
	void shorten()
	{
		long long gcd = std::__gcd(num_, denom_);
		num_ /= gcd;
		denom_ /= gcd;
	}
};

#endif /* FRACTION_H */