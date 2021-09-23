#include "TBitField.h"

uint TBitField::GetMemIndex(const uint n) const
{
	return n >> 5;
}

uint TBitField::GetMemMask(const uint n) const
{
	return 1 << (n & (8 * sizeof(uint) - 1));
}

void TBitField::updateMem(uint*& mem, uint parts)
{
	assert(parts != 0);
	uint* buf = new uint[parts];
	for (uint i = 0; i < parts - 1; i++)
		buf[i] = mem[i];
	buf[parts - 1] = 0;
	delete[]mem;
	mem = buf;
}

TBitField::TBitField(uint len) :BitLen(len)
{
	assert(len > 0);
	MemLen = len / (sizeof(uint) * 8) + len % (sizeof(uint) * 8);
	pMem = new uint[MemLen];
	for (uint i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf)
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new uint[MemLen];
	for (uint i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

uint TBitField::GetLength() const
{
	return BitLen;
}

void TBitField::SetBit(const uint n)
{
	assert(n <= BitLen);
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClearBit(const uint n)
{
	assert(n <= BitLen);
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

uint TBitField::GetBit(const uint n) const
{
	if (n > BitLen)
		return 0;
	else
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1;
}

bool TBitField::operator==(const TBitField& bf)
{
	if (BitLen != bf.BitLen)
		return false;
	if (MemLen != bf.MemLen)
		return false;
	for (uint i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return false;
	return true;
}

bool TBitField::operator!=(const TBitField& bf)
{
	if (BitLen != bf.BitLen || MemLen != bf.MemLen)
		return true;
	for (uint i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return true;
	return false;
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	delete[] pMem;
	this->pMem = new uint[MemLen];
	for (uint i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
	// TODO: вставьте здесь оператор return
}

TBitField TBitField::operator&(const TBitField& bf)
{
	uint len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (uint i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (uint i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	uint len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (uint i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (uint i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~()
{
	TBitField tmp(BitLen);
	for (uint i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~tmp.pMem[i];
	}
	return tmp;
}

std::istream& operator>>(std::istream& in, TBitField& bf)
{
	uint* mem = new uint[1];
	mem[0] = 0;
	uint size = 0;
	char input;
	do
	{
		in >> input;
		if (input == '1')
			mem[size >> 5] |= 1 << (size & (8 * sizeof(uint) - 1));
		else if (input != '0')
			break;
		size++;
		if (size % 32 == 0)
			bf.updateMem(mem, (size >> 5) + 1);
	} while (input == '0' || input == '1');

	bf = TBitField(size);
	delete bf.pMem;
	bf.pMem = mem;
	return in;
}

ostream& operator<<(ostream& out, const TBitField& bf)
{

	for (uint i = 0; i < bf.BitLen; i++)
		out << bf.GetBit(i);
	return out;
	/*
	for (uint i = 0; i < bf.MemLen; i++)
		out << std::bitset<32>(bf.pMem[i]) << ' ';
	*/
}
