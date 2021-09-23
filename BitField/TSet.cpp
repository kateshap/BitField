#include "TSet.h"

TSet::TSet(uint size) :MaxPower(size), BitField(size)
{
}

TSet::TSet(const TSet& ts) : MaxPower(ts.MaxPower), BitField(ts.BitField)
{
}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

uint TSet::GetMaxPower()
{
	return this->MaxPower;
}

void TSet::InsElem(const uint n)
{
	BitField.SetBit(n);
}

void TSet::DelElem(const uint n)
{
	BitField.ClearBit(n);
}

bool TSet::IsMember(const uint n)
{
	return BitField.GetBit(n) > 0 ? true : false;
}

bool TSet::operator==(const TSet& ts)
{
	if (MaxPower != ts.MaxPower || BitField != ts.BitField)
		return false;
	return true;
}

TSet& TSet::operator=(const TSet& ts)
{
	BitField = ts.BitField;
	MaxPower = ts.MaxPower;
	return *this;
	// TODO: вставьте здесь оператор return
}

TSet& TSet::operator+(const uint n)
{
	TSet ts(*this);
	ts.InsElem(n);
	return ts;
	// TODO: вставьте здесь оператор return
}

TSet& TSet::operator-(const uint n)
{
	TSet ts(*this);
	ts.DelElem(n);
	return ts;
	// TODO: вставьте здесь оператор return
}

TSet& TSet::operator|(const TSet& ts)
{
	TSet tmp(BitField | ts.BitField);
	return tmp;
	// TODO: вставьте здесь оператор return
}

TSet& TSet::operator&(const TSet& ts)
{
	TSet tmp(BitField & ts.BitField);
	return tmp;
	// TODO: вставьте здесь оператор return
}

TSet TSet::operator~()
{
	TSet ts(~BitField);
	return ts;
}

istream& operator>>(istream& in, TSet& ts)
{
	uint tmp;
	char ch;
	do
	{
		in >> ch;

	} while (ch != '{');
	do
	{
		in >> tmp;
		ts.InsElem(tmp);
		do
		{
			in >> ch;
		} while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return in;
}

ostream& operator<<(ostream& out, TSet& ts)
{
	
	out << '{';
	for (uint i = 0; i < ts.GetMaxPower(); i++)
	{
		if (ts.IsMember(i))
		{
			out << i << '  ';
			//if (ts.IsMember(i + 1))
				//out << ', ';
		}
	}
	out << '}';
	return out;
	// TODO: вставьте здесь оператор return
	
	/*
	out << '{';
	std::string buf;
	for (int32_t i = 0; i < ts.GetMaxPower(); i++) {
		if (ts.IsMember(i)) {
			buf += std::to_string(i);
			buf += ", ";
		}
	}

	out << (!buf.empty() ? std::string(buf.begin(), buf.end() - 2) : std::string(" ")) << '}';

	return out;
	*/
}
