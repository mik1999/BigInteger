#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

typedef long long NumType;
class BigInteger
{
private:
	vector <NumType> digit_;
	bool negative_;
	static const NumType Mod_ = 100000, LogMod_ = 5;
	BigInteger& sum_(const BigInteger& num);//-----
	BigInteger& diff_(const BigInteger& num);//-----
	friend const BigInteger mul(const BigInteger &num1, const BigInteger &num2);//-----
	friend const BigInteger quickMul(const BigInteger &num1, const BigInteger &num2);//-----
	friend const BigInteger operator / (const BigInteger &num1, NumType num);
	friend const BigInteger operator / (const BigInteger &num1, const BigInteger &num2);
	friend void solve();
	friend BigInteger randBig(size_t size);//-----
	friend istream& operator >>(istream& in, BigInteger& num); //-----
	friend ostream& operator <<(ostream& out, const BigInteger& num);//-----
	void leadZero_();//-----
	void opposite_();//-----
	NumType& back_();//-----
	NumType back_() const;//-----
	NumType& operator [](size_t index);//-----
	NumType operator [](size_t index) const;//-----
	size_t size() const;//-----
	bool zero_() const;//-----
	void inc_();//-----
	void dec_();//-----
	void shift(int sh);//-----
public:
	BigInteger();//-----
	BigInteger(NumType num);//-----
	BigInteger(const string& s);//-----
	~BigInteger();//-----
	bool negative() const;//-----
	explicit operator bool() const;//-----
	explicit operator int() const;//-----
	explicit operator long long() const;//-----
	explicit operator string() const;//-----
	string toString() const;//-----
	bool absEqual(const BigInteger& num) const;
	bool absLess(const BigInteger& num) const;
	BigInteger operator -() const;//-----
	BigInteger& operator += (const BigInteger& num);//-----
	BigInteger& operator -= (const BigInteger& num);//-----
	BigInteger& operator *= (const BigInteger& num);
	BigInteger& operator /= (const BigInteger& num);
	BigInteger& operator %= (const BigInteger& num);
	BigInteger& operator++();//-----
	const BigInteger operator++(int);//-----
	BigInteger& operator--();//-----
	const BigInteger operator--(int);//-----
};

const BigInteger operator + (const BigInteger &num1, const BigInteger &num2);//-----
const BigInteger operator - (const BigInteger &num1, const BigInteger &num2);//-----
const BigInteger operator * (const BigInteger &num1, const BigInteger &num2);
const BigInteger operator / (const BigInteger &num1, NumType num2);
const BigInteger operator / (const BigInteger &num1, const BigInteger &num2);
const BigInteger operator % (const BigInteger &num1, const BigInteger &num2);

const bool operator ==(const BigInteger& a, const BigInteger& b);//-----
const bool operator <(const BigInteger& a, const BigInteger& b);//-----
const bool operator >(const BigInteger& a, const BigInteger& b);//-----
const bool operator <=(const BigInteger& a, const BigInteger& b);//-----
const bool operator >=(const BigInteger& a, const BigInteger& b);//-----
const bool operator !=(const BigInteger& a, const BigInteger& b);//-----

BigInteger randBig(size_t size);//-----