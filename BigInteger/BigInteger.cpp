#include "BigInteger.h"

BigInteger::BigInteger()
{
	digit_.push_back(0);
	negative_ = false;
}

BigInteger::BigInteger(NumType num)
{
	negative_ = num < 0;
	if (num < 0)
		num = -num;
	do {
		digit_.push_back(num % Mod_);
		num /= Mod_;
	} while (num > 0);
}

BigInteger::BigInteger(const string& s)
{
	string str = s;
	negative_ = false;
	if (str[0] == '-') {
		str.erase(0, 1);
		negative_ = true;
	}
	while (str.size() >= LogMod_) {
		NumType t = 0;
		for (size_t i = str.size() - LogMod_; i < str.size(); i++)
			t = t * 10 + (str[i] - '0');
		for (int i = 0; i < LogMod_; i++)
			str.pop_back();
		digit_.push_back(t);
	}
	if (!str.empty())
		digit_.push_back(0);
	for (size_t i = 0; i < str.size(); i++)
		back_() = back_() * 10 + (str[i] - '0');
}

BigInteger::~BigInteger()
{
}

BigInteger::operator bool() const {
	return !zero_();
}

BigInteger::operator int() const {
	int ans = 0;
	for (size_t i = size() - 1;; i--) {
		ans = ans * Mod_ + digit_[i];
		if (i == 0)
			break;
	}
	if (negative())
		ans *= -1;
	return ans;
}

BigInteger::operator long long() const {
	long long ans = 0;
	for (size_t i = size() - 1;; i--){
		ans = ans * Mod_ + digit_[i];
		if (i == 0)
			break;
	}
	if (negative())
		ans *= -1;
	return ans;
}

BigInteger::operator string() const {
	string ans = "";
	if (negative())
		ans += "-";
	ans += to_string(back_());
	if (size() == 1)
		return ans;
	for (size_t i = size() - 2;; i--) {
		NumType t = digit_[i];
		if (t == 0) {
			for (size_t j = 0; j < LogMod_; j++)
				ans += "0";
		}
		else {
			for (; t * 10 < Mod_; t *= 10)
				ans += "0";
			ans += to_string(digit_[i]);
		}
		if (i == 0)
			break;
	}
	return ans;
}

string BigInteger::toString() const{
	return operator string();
}

istream& operator >>(istream& in, BigInteger& num) {
	string s;
	in >> s;
	num = BigInteger(s);
	return in;
}

ostream& operator <<(ostream& out, const BigInteger& num) {
	out << num.toString();
	return out;
}

size_t BigInteger::size() const{
	return digit_.size();
}

NumType& BigInteger::back_() {
	return digit_[size() - 1];
}

NumType BigInteger::back_() const {
	return digit_[size() - 1];
}

NumType BigInteger::operator [](size_t index) const{
	return digit_[index];
}

NumType& BigInteger::operator [](size_t index){
	return digit_[index];
}

void BigInteger::leadZero_() {
	while (size() > 1 && back_() == 0)
		digit_.pop_back();
	if (zero_())
		negative_ = false;
}

void BigInteger::opposite_() {
	if (!zero_())
		negative_ ^= 1;
}

bool BigInteger::zero_() const{
	return (size() == 1 && digit_[0] == 0);
}

bool BigInteger::negative() const{
	return negative_;
}

void BigInteger::shift(int sh) {
	digit_.resize(size() + sh);
	rotate(digit_.begin(), digit_.end() - sh, digit_.end());
}

void BigInteger::inc_() {
	digit_[0]++;
	for (size_t i = 0; digit_[i] == Mod_ && i + 1 < size(); i++) {
		digit_[i] = 0;
		digit_[i + 1]++;
	}
	if (back_() == Mod_) {
		back_() = 0;
		digit_.push_back(1);
	}
}
void BigInteger::dec_() {
	digit_[0]--;
	for (size_t i = 0; digit_[i] < 0; i++) {
		digit_[i + 1]--;
		digit_[i] = Mod_ - 1;
	}
	leadZero_();
}

BigInteger& BigInteger::operator++() {
	if (negative()) {
		dec_();
		if (zero_())
			negative_ = false;
	}
	else
		inc_();
	return *this;
}

const BigInteger BigInteger::operator++(int) {
	BigInteger old = *this;
	if (negative()) {
		dec_();
		if (zero_())
			negative_ = false;
	}
	else
		inc_();
	return old;
}

BigInteger& BigInteger::operator--() {
	if (zero_()) {
		inc_();
		negative_ = true;
	}
	else if (negative())
		inc_();
	else dec_();
	return *this;
}

const BigInteger BigInteger::operator--(int) {
	BigInteger old = *this;
	if (zero_()) {
		inc_();
		negative_ = true;
	}
	else if (negative())
		inc_();
	else dec_();
	return old;
}

bool BigInteger::absEqual(const BigInteger& num) const{
	if (size() != num.size())
		return false;
	for (size_t i = 0; i < size(); i++)
		if (this->digit_[i] != num[i])
			return false;
	return true;
}

bool BigInteger::absLess(const BigInteger& num) const{
	if (size() != num.size())
		return size() < num.size();
	for (size_t i = size() - 1;; i--) {
		if (digit_[i] != num[i])
			return digit_[i] < num[i];
		if (i == 0)
			break;
	}
	return false;
}

const bool operator ==(const BigInteger& a, const BigInteger& b) {
	return a.negative() == b.negative() && a.absEqual(b);
}

const bool operator <(const BigInteger& a, const BigInteger& b) {
	if (a.negative() != b.negative())
		return a.negative();
	return a.negative() ? b.absLess(a) : a.absLess(b);
}

const bool operator >(const BigInteger& a, const BigInteger& b) {
	if (a.negative() != b.negative())
		return b.negative();
	return a.negative() ? a.absLess(b) : b.absLess(a);
}

const bool operator <=(const BigInteger& a, const BigInteger& b) {
	return !(a > b);
}

const bool operator >=(const BigInteger& a, const BigInteger& b) {
	return !(a < b);
}
 
const bool operator !=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

BigInteger BigInteger::operator -() const {
	BigInteger ans = *this;
	ans.opposite_();
	return ans;
}

BigInteger& BigInteger::sum_(const BigInteger& num){
	BigInteger& ans = *this;
	digit_.resize(max(size(), num.size()) + 1);
	for (size_t i = 0; i < num.size(); i++) {
		ans[i + 1] += (ans[i] + num[i]) / Mod_;
		ans[i] = (ans[i] + num[i]) % Mod_;
	}
	for (size_t i = num.size(); ans[i] == Mod_; i++) {
		ans[i] = 0;
		ans[i + 1]++;
	}
	ans.leadZero_();
	return ans;
}
BigInteger& BigInteger::diff_(const BigInteger& num) {
	BigInteger& ans = *this;
	for (int i = 0; i < (int)num.size(); i++) {
		ans[i] -= num[i];
		if (ans[i] < 0) {
			ans[i + 1]--;
			ans[i] += Mod_;
		}
	}
	for (int i = num.size(); i < (int)ans.size(); i++)
		if (ans[i] < 0) {
			ans[i] += Mod_;
			ans[i + 1]--;
		}
	ans.leadZero_();
	return ans;
}

BigInteger& BigInteger::operator += (const BigInteger& num) {
	if (negative() == num.negative())
		sum_(num);
	else if (absLess(num)) {
		BigInteger t = num;
		t.diff_(*this);
		*this = t;
	}
	else
		diff_(num);
	return *this;
}

BigInteger& BigInteger::operator -= (const BigInteger& num) {
	if (negative() != num.negative())
		sum_(num);
	else if (absLess(num)) {
		BigInteger t = num;
		t.diff_(*this);
		t.opposite_();
		*this = t;
	}
	else
		diff_(num);
	return *this;
}

const BigInteger operator + (const BigInteger &num1, const BigInteger &num2) {
	BigInteger ans = num1;
	ans += num2;
	return ans;
}

const BigInteger operator - (const BigInteger &num1, const BigInteger &num2) {
	BigInteger ans = num1;
	ans -= num2;
	return ans;
}

const BigInteger mul(const BigInteger &num1, const BigInteger &num2) {
	BigInteger ans;
	ans.digit_.resize(num1.size() + num2.size() + 1);
	for (size_t i = 0; i < num1.size(); i++)
		for (int j = 0; j < (int)num2.size(); j++) {
			ans[i + j] += num1[i] * num2[j];
			ans[i + j + 1] += ans[i + j] / BigInteger::Mod_;
			ans[i + j] %= BigInteger::Mod_;
		}
	for (size_t i = 0; i < ans.size() - 1; i++) {
		ans[i + 1] += ans[i] / BigInteger::Mod_;
		ans[i] %= BigInteger::Mod_;
	}
	ans.negative_ = num1.negative() ^ num2.negative();
	ans.leadZero_();
	return ans;
}

const int MinMul = 239, MinMin = 6;

const BigInteger quickMul(const BigInteger &num1, const BigInteger &num2) {
	if (num1.size() * num2.size() < MinMul || min(num1.size(), num2.size()) < MinMin)
		return mul(num1, num2);
	size_t pos = min(num1.size(), num2.size()) / 2;
	BigInteger a, b, c, d;
	a.digit_.resize(pos);
	copy(num1.digit_.begin(), num1.digit_.begin() + pos, a.digit_.begin());
	b.digit_.resize(num1.size() - pos);
	copy(num1.digit_.begin() + pos, num1.digit_.end(), b.digit_.begin());
	c.digit_.resize(pos);
	copy(num2.digit_.begin(), num2.digit_.begin() + pos, c.digit_.begin());
	d.digit_.resize(num2.size() - pos);
	copy(num2.digit_.begin() + pos, num2.digit_.end(), d.digit_.begin());
	BigInteger ac = quickMul(a, c), bd = quickMul(b, d), t = quickMul(a + b, c + d), s = t - ac - bd;
	s.shift(pos);
	bd.shift(2 * pos);
	BigInteger ans = ac + s + bd;
	ans.negative_ = num1.negative_ ^ num2.negative_;
	if (ans.zero_())
		ans.negative_ = false;
	return ans;
}

const BigInteger operator * (const BigInteger &num1, const BigInteger &num2) {
	return quickMul(num1, num2);
}

BigInteger& BigInteger::operator *= (const BigInteger& num) {
	*this = *this * num;
	return *this;
}

const BigInteger operator / (const BigInteger &num1, NumType num2) {
	BigInteger ans = num1;
	for (size_t i = num1.size() - 1; i > 0; i--) {
		ans[i - 1] += BigInteger::Mod_*(ans[i] % num2);
		ans[i] /= num2;
	}
	ans[0] /= num2;
	ans.leadZero_();
	return ans;
}

const BigInteger operator / (const BigInteger &num1, const BigInteger &num2) {
	assert(num2 != 0);
	if (num1.size() < num2.size())
		return 0;
	BigInteger dividend = num1, divider = num2, ans;
	ans.digit_.resize(num1.size() + 1 - num2.size());
	divider.shift(num1.size() - num2.size());
	for (size_t i = num1.size() - num2.size();; i--) {
		
		if (i == 0)
			break;
	}
	return 0;
}

BigInteger& BigInteger::operator /= (const BigInteger& num) {
	*this = *this / num;
	return *this;
}

const BigInteger operator % (const BigInteger &num1, const BigInteger &num2) {
	return num1 - num2 * (num1 / num2);
}

BigInteger& BigInteger::operator %= (const BigInteger& num) {
	*this = *this % num;
	return *this;
}


BigInteger randBig(size_t size) {
	BigInteger ans = 1;
	ans.shift(size);
	for (size_t i = 0; i < size; i++)
		ans.digit_[i] = rand() % BigInteger::Mod_;
	return ans;
}