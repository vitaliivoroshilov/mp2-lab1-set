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
    BitLen = len;
    MemLen = ((BitLen - 1) / (sizeof(TELEM) * 8) + 1);
    pMem = new TELEM[MemLen];
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
    /*TBitField res(BitLen);
    for (int i = 0; i < res.BitLen; i++)
        pMem[i] = 0;
    pMem[n / (sizeof(TELEM) * 8)] = 1;
    return res;*/
    return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    //pMem[n / (sizeof(TELEM) * 8)] = 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    //pMem[n / (sizeof(TELEM) * 8)] = 0;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return FAKE_INT;//pMem[n / (sizeof(TELEM) * 8)];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf)
        return *this;
    BitLen = bf.BitLen;
    if (MemLen < bf.MemLen)
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
    if (BitLen != bf.BitLen) throw std::invalid_argument("");
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen != bf.BitLen) throw std::invalid_argument("");
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        /*if (pMem[i] == 0)
            pMem[i] = 1;
        if (pMem[i] == 1)
            pMem[i] = 0;*/
        res.pMem[i] = ~pMem[i];
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    /*for (int i =  0; i < bf.BitLen; i++)
        istr >> bf.pMem[i];*/
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    /*for (int i = bf.BitLen - 1; i >= 0; i--)
        ostr << bf.pMem[i];*/
    return ostr;
}
