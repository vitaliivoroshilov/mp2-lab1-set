// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
        throw invalid_argument("");

    BitLen = len;
    MemLen = ((BitLen - 1) / (sizeof(TELEM) * 8) + 1);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n > BitLen)) throw invalid_argument("");
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n > BitLen)) throw invalid_argument("");
    return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen)) throw invalid_argument("");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen)) throw invalid_argument("");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen)) throw invalid_argument("");
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
        return *this;

    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen)
    {
        TELEM* tmp = new TELEM[MemLen];
        delete[] pMem;
        pMem = tmp;
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;

    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) != bf.GetBit(i))
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int lowerBitLen, biggerBitLen;
    if (BitLen >= bf.BitLen)
    {
        lowerBitLen = bf.BitLen;
        biggerBitLen = BitLen;
    }
    else
    {
        lowerBitLen = BitLen;
        biggerBitLen = bf.BitLen;
    }
    TBitField biggerBitField(biggerBitLen);
    if (BitLen >= bf.BitLen)
        biggerBitField = *this;
    else
        biggerBitField = bf;

    TBitField res(biggerBitField);
    for (int i = 0; i < lowerBitLen; i++)
        if (GetBit(i) | bf.GetBit(i))
            res.SetBit(i);
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int resBitLen, lowBitLen;
    if (BitLen >= bf.BitLen)
    {
        resBitLen = BitLen;
        lowBitLen = bf.BitLen;
    }
    else
    {
        resBitLen = bf.BitLen;
        lowBitLen = BitLen;
    }
    TBitField res(resBitLen);
    for (int i = 0; i < lowBitLen; i++)
        if (GetBit(i) & bf.GetBit(i))
            res.SetBit(i);
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (!GetBit(i))
            res.SetBit(i);
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    int bit = 0;
    for (int i = bf.BitLen - 1; i >= 0; i--)
    {
        istr >> bit;
        if (bit)
            bf.SetBit(i);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        if (bf.GetBit(i))
            ostr << "1";
        else
            ostr << "0";
    ostr << endl;
    return ostr;
}