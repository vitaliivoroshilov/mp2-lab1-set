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
    if (len < 1)
        throw invalid_argument("");

    BitLen = len;
    MemLen = ((BitLen - 1) / (sizeof(TELEM) * 8) + 1);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen)
        throw out_of_range("");
    if (n < 0)
        throw invalid_argument("");

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen)
        throw out_of_range("");
    if (n < 0)
        throw invalid_argument("");

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen)
        throw out_of_range("");
    if (n < 0)
        throw invalid_argument("");

    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) > 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf)
        return *this;

    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen)
    {
        TELEM *tmp = new TELEM[MemLen];
        delete[] pMem;
        pMem = tmp;
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return false;

    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return false;
    return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen)
        return false;

    for (int i = 0; i < MemLen; i++)
        if (pMem[i] == bf.pMem[i])
            return false;
    return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen != bf.BitLen)
        throw length_error("");
    /*{
        if (BitLen > bf.BitLen)
        {
            TBitField tmp(BitLen);
            for (int i = MemLen; i > MemLen - bf.MemLen; i--)
                tmp.pMem[i] = bf.pMem[i];
            delete[] bf.pMem;
            TBitField res(BitLen);
            for (int i = 0; i < MemLen; i++)
                res.pMem[i] = pMem[i] | tmp.pMem[i];
            return res;
        }
            TBitField tmp(bf.BitLen);
            for (int i = bf.MemLen; i > bf.MemLen - MemLen; i--)
                tmp.pMem[i] = pMem[i];
            delete[] pMem;
            TBitField res(bf.BitLen);
            for (int i = 0; i < bf.MemLen; i++)
                res.pMem[i] = tmp.pMem[i] | bf.pMem[i];
            return res;
    }*/
    TBitField res(bf.BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen != bf.BitLen)
        throw length_error("");

    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = ~pMem[i];
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
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

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        if (bf.GetBit(i))
            ostr << "1";
        else
            ostr << "0";
    return ostr;
}
