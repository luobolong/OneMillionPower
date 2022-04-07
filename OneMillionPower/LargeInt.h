#pragma once
#include <bitset>
#include <vector>
typedef unsigned long long size_t;

template <size_t _Digits>
class LargeInt
{
private:
	std::bitset<_Digits> _dta{0};
	size_t _len;
public:
	LargeInt()
	{
		this->_len = (size_t)0;
	}

	LargeInt(const std::bitset<_Digits> dta, const size_t len)
	{
		set_len(len);
		set_dta(dta);
	}

	void set_len(const size_t len)
	{
		if (len > _Digits)
		{
			throw "The length shall not be larger than the digits of the bitset";
		}
		this->_len = len;
	}

	size_t& get_len()
	{
		return this->_len;
	}

	void set_dta(const std::bitset<_Digits>& dta)
	{
		if (dta[_len - 1] == 0)
		{
			throw "Data does not match with the length";
		}
		this->_dta = dta;
	}

	std::bitset<_Digits>& get_dta()
	{
		return this->_dta;
	}

	void add(const LargeInt& li)
	{
		size_t max_len = this->_len > li._len ? this->_len : li._len;
		if (max_len < _Digits)
		{
			size_t max_len_p1 = max_len + 1;
			bool carry = false;
			for (size_t i = 0; i < max_len_p1; ++i)
			{
				bool tmp = this->_dta[i];
				this->_dta[i] = (tmp ^ li._dta[i]) ^ carry;
				carry = (tmp && li._dta[i]) || (tmp && carry) || (li._dta[i] && carry);
			}
			if (this->_dta[max_len] == 1)
			{
				this->set_len(max_len_p1);
			}
			else
			{
				this->set_len(max_len);
			}
		}
		else if (max_len == _Digits)
		{
			size_t max_len_m1 = max_len - 1;
			auto reserved = *this;
			this->set_len(max_len);
			bool carry = false;
			for (size_t i = 0; i < max_len; ++i) {
				bool tmp = this->_dta[i];
				this->_dta[i] = (tmp ^ li._dta[i]) ^ carry;
				carry = (tmp && li._dta[i]) || (tmp && carry) || (li._dta[i] && carry);
				if (i == max_len_m1 && carry == true)
				{
					*this = reserved;
					throw "LargeInt data overflow";
				}
			}
		}
		else
		{
			throw "LargeInt data overflow";
		}
	}

	void pow(size_t p)
	{
		if (p == 0)
		{
			this->set_len(1);
			this->set_dta(std::bitset<_Digits>{1});
			return;
		}
		if (p == 1)
		{
			return;
		}
		std::vector<size_t> shift_offsets;
		for (size_t i = 0; i < this->_len; ++i)
		{
			if (this->_dta[i] == 1)
			{
				shift_offsets.push_back(i);
			}
		}

		for (size_t i = 1; i < p; ++i)
		{
			LargeInt<_Digits> tmp = *this;
			this->set_len(0);
			this->_dta.reset();
			for (auto iter = shift_offsets.begin(); iter < shift_offsets.end(); ++iter)
			{
				this->add(LargeInt<_Digits>(tmp._dta << *iter, tmp._len + *iter));
			}
		}
	}
};