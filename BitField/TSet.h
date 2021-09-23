#pragma once
#include "TBitField.h"

class TSet
{
private:
	uint MaxPower;
	TBitField BitField;
public:
	TSet(uint size);
	TSet(const TSet& ts);
	TSet(const TBitField& bf);
	operator TBitField();
	uint GetMaxPower();
	void InsElem(const uint n);
	void DelElem(const uint n);
	bool IsMember(const uint n);
	bool operator==(const TSet& ts);
	TSet& operator=(const TSet& ts);
	TSet& operator+(const uint n);
	TSet& operator-(const uint n);
	TSet& operator|(const TSet& ts);
	TSet& operator&(const TSet& ts);
	TSet operator~();
	friend istream& operator>>(istream& in, TSet& ts);
	friend ostream& operator<<(ostream& out, TSet& ts);
};

