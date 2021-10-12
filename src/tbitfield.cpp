// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw("Error: negative lenght not allowed");
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > 0) && (n < BitLen - 1))
		return n / (sizeof(TELEM) << 3);
	else
		throw ("Error: out of range");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > 0) && (n < BitLen - 1))
		return 1 << n % (sizeof(TELEM) << 3);
	else
		throw ("Error: out of range");
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int index;
		index = GetMemIndex(n);
		pMem[index] |= GetMemMask(n);
	}
	else
		throw ("Error: the bit does not exist");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int index;
		index = GetMemIndex(n);
		pMem[index] &= (~(GetMemMask(n)));

	}
	else
		throw ("Error: the bit does not exist");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
	{
		int index;
		index = GetMemIndex(n);
		if (pMem[index] & GetMemMask(n))
		{
			return 1;
		}
		else
			return 0;
	}
	else
		throw ("Error: the bit does not exist");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete[]pMem;
		this->BitLen = bf.BitLen;
		this->MemLen = bf.MemLen;
		this->pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int flag = 0;

	if (BitLen != bf.BitLen) return 0;

	for (int i = 0; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i))
			flag++;
		else
			continue;
	}

	if (flag) return 0;
	else return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int flag;
	if (BitLen >= bf.BitLen)
		flag = 1;
	else
		flag = 0;

	int m;
	if (flag)
		m = bf.BitLen;
	else
		m = BitLen;

	TBitField res = flag ? (*this) : bf;

	for (int i = 0; i < m; i++) {
		if (GetBit(i) | bf.GetBit(i)) res.SetBit(i);
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len, mem;
	if (BitLen > bf.BitLen)
	{
		len = BitLen;
		mem = bf.MemLen;
	}
	else
	{
		len = bf.BitLen;
		mem = MemLen;
	}

	TBitField temp(len);

	for (int i = 0; i < mem; i++)
		temp.pMem[i] = pMem[i] & bf.pMem[i];

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != 0)
			temp.ClrBit(i);
		else
			temp.SetBit(i);
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int tmp;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> tmp;
		if (tmp)
			bf.SetBit(tmp);
		else
			bf.ClrBit(tmp);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int i = 0;
	while (i < bf.BitLen)
	{
		ostr << bf.GetBit(i) << ' ';
		i++;
	}
	return ostr;
}
