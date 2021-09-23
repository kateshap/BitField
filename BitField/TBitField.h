#pragma once
#include <iostream>
#include <cassert>
#include <bitset>
typedef unsigned int uint;
using namespace std;

class TBitField
{
private:
	uint BitLen;
	uint MemLen;
	uint* pMem;
	uint GetMemIndex(const uint n) const;
	uint GetMemMask(const uint n) const;
	void updateMem(uint*& mem, uint parts);
public:
	TBitField(uint len);
	TBitField(const TBitField& bf);
	~TBitField();
	uint GetLength() const;
	void SetBit(const uint n);
	void ClearBit(const uint n);
	uint GetBit(const uint n) const;
	bool operator ==(const TBitField& bf);
	bool operator !=(const TBitField& bf);
	TBitField& operator =(const TBitField& bf);
	TBitField operator &(const TBitField& bf);
	TBitField operator |(const TBitField& bf);
	TBitField operator ~();
	friend std::istream& operator >>(std::istream& ist, TBitField& bf);
	friend std::ostream& operator <<(std::ostream& out, const TBitField& bf);
};