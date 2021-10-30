// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}


// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
    TBitField bf(BitField);
    return bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem >= MaxPower)) 
        throw ("Error: canot check an element because the elem does not exist");
    
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw ("Error: canot insert an element because the elem does not exist");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw ("Error: canot delete an element because the elem does not exist");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (BitField != s.BitField) return 0;
    return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    if ((*this) == s) return 0;
    else return 1;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet res((*this).BitField | s.BitField);
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet temp((BitField) & (s.BitField));
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int i;
    istr >> i;
    s.InsElem(i);
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    int el;
    for (int i = 0; i < s.MaxPower; i++) {
        el = s.BitField.GetBit(i);
        if (el)
            ostr << i << " ";
    }
    return ostr;
}