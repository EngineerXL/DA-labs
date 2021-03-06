#ifndef BIG_NUM_LIB_HPP
#define BIG_NUM_LIB_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class TBigNum {
private:
    const static int64_t BASE = 10;
    const static int64_t RADIX = 4;
    const static int64_t MAX_DIGIT = 1e4;

    std::vector<int64_t> Data;

    void Normalize() {
        while (Data.size() > 1 and Data.back() == 0) {
            Data.pop_back();
        }
        std::reverse(Data.begin(), Data.end());
    }

    static void DivMod(const TBigNum & lhs, const TBigNum & rhs, TBigNum & div, TBigNum & mod) {
        if (lhs.Size() < rhs.Size()) {
            div = TBigNum("0");
            mod = lhs;
            return;
        }
        TBigNum res(lhs.Size());
        TBigNum tmp(rhs.Size());
        tmp.Data.back() = lhs.Data[0];
        TBigNum shiftFactor(2);
        shiftFactor.Data[0] = 1;
        for (size_t i = 0; i < lhs.Size(); ++i) {
            int64_t l = -1;
            int64_t r = TBigNum::MAX_DIGIT;
            TBigNum factor(1);
            while (l + 1 < r) {
                int64_t m = (l + r) / 2;
                factor.Data[0] = m;
                if (factor * rhs > tmp) {
                    r = m;
                } else {
                    l = m;
                }
            }
            res.Data[res.Size() - i - 1] = l;
            factor.Data[0] = l;
            tmp = (tmp - factor * rhs) * shiftFactor;
            if (i + 1 < lhs.Size()) {
                tmp.Data.back() = lhs.Data[i + 1];
            }
        }
        res.Normalize();
        div = res;
        mod = tmp;
    }
public:
    TBigNum() = default;

    TBigNum(const size_t & size) : Data(size) {}

    TBigNum(const TBigNum & num) : Data(num.Data) {}

    TBigNum(const std::string & s) {
        size_t n = s.size();
        Data.resize((n + RADIX - 1) / RADIX);
        for (size_t i = 0; i < Data.size(); ++i) {
            int64_t digit = 0;
            for (int64_t j = 0; j < TBigNum::RADIX; ++j) {
                int64_t ind = n - (i + 1) * TBigNum::RADIX + j;
                if (ind >= 0) {
                    digit = digit * TBigNum::BASE + s[ind] - '0';
                }
            }
            Data[Data.size() - 1 - i] = digit;
        }
    }

    TBigNum & operator = (const TBigNum & num) {
        Data = num.Data;
        return *this;
    }

    size_t Size() const {
        return Data.size();
    }

	friend TBigNum operator + (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.Size() < rhs.Size()) {
            return rhs + lhs;
        }
        TBigNum res(lhs.Size());
        bool flag = false;
        for (size_t i = 0; i < lhs.Size(); ++i) {
            int64_t sum;
            if (i > rhs.Size() - 1) {
                sum = lhs.Data[lhs.Size() - i - 1];
            } else {
                sum = lhs.Data[lhs.Size() - i - 1] + rhs.Data[rhs.Size() - i - 1];
            }
            if (flag) {
                ++sum;
            }
            if (sum >= TBigNum::MAX_DIGIT) {
                sum = sum - TBigNum::MAX_DIGIT;
                flag = true;
            } else {
                flag = false;
            }
            res.Data[i] = sum;
        }
        if (flag) {
            res.Data.push_back(1);
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator - (const TBigNum & lhs, const TBigNum & rhs) {
        TBigNum res(lhs.Size());
        bool flag = false;
        for (size_t i = 0; i < lhs.Size(); ++i) {
            int64_t diff;
            if (i > rhs.Size() - 1) {
                diff = lhs.Data[lhs.Size() - i - 1];
            } else {
                diff = lhs.Data[lhs.Size() - i - 1] - rhs.Data[rhs.Size() - i - 1];
            }
            if (flag) {
                --diff;
            }
            if (diff < 0) {
                diff = diff + TBigNum::MAX_DIGIT;
                flag = true;
            } else {
                flag = false;
            }
            res.Data[i] = diff;
        }
        if (flag) {
            --res.Data.back();
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator * (const TBigNum & lhs, const TBigNum & rhs) {
        TBigNum res(lhs.Size() + rhs.Size());
        for (size_t i = 0; i < lhs.Size(); ++i) {
            for (size_t j = 0; j < rhs.Size(); ++j) {
                res.Data[i + j] = res.Data[i + j] + lhs.Data[lhs.Size() - i - 1] * rhs.Data[rhs.Size() - j - 1];
            }
        }
        for (size_t i = 0; i < res.Size() - 1; ++i) {
            res.Data[i + 1] = res.Data[i + 1] + res.Data[i] / TBigNum::MAX_DIGIT;
            res.Data[i] = res.Data[i] % TBigNum::MAX_DIGIT;
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator ^ (TBigNum lhs, TBigNum rhs) {
        TBigNum res("1");
        TBigNum two("2");
        while (rhs.Size() > 0 and rhs.Data[0] > 0) {
            TBigNum div, mod;
            DivMod(rhs, two, div, mod);
            if (mod.Data[0] > 0) {
                res = res * lhs;
            }
            lhs = lhs * lhs;
            rhs = div;
        }
        return res;
    }

    friend TBigNum operator / (const TBigNum & lhs, const TBigNum & rhs) {
        TBigNum div, mod;
        DivMod(lhs, rhs, div, mod);
        return div;
    }

    friend bool operator < (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.Size() != rhs.Size()) {
            return lhs.Size() < rhs.Size();
        }
        for (size_t i = 0; i < lhs.Size(); ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] < rhs.Data[i];
            }
        }
        return false;
    }

    friend bool operator > (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.Size() != rhs.Size()) {
            return lhs.Size() > rhs.Size();
        }
        for (size_t i = 0; i < lhs.Size(); ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] > rhs.Data[i];
            }
        }
        return false;
    }

    friend bool operator == (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.Size() != rhs.Size()) {
            return false;
        }
        for (size_t i = 0; i < lhs.Size(); ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream & operator << (std::ostream & out, const TBigNum & num) {
        out << num.Data[0];
        for (size_t i = 1; i < num.Size(); ++i) {
            int64_t curDigit = TBigNum::MAX_DIGIT / TBigNum::BASE;
            while (curDigit >= TBigNum::BASE - 1 and num.Data[i] / curDigit == 0) {
                out << '0';
                curDigit = curDigit / TBigNum::BASE;
            }
            out << num.Data[i];
        }
        return out;
    }

    friend std::istream & operator >> (std::istream & in, TBigNum & num) {
        std::string s;
        in >> s;
        size_t i = 0;
        while (i < s.size() and s[i] == '0') {
            ++i;
        }
        if (i == s.size()) {
            num = TBigNum("0");
        } else {
            num = TBigNum(s.substr(i, s.size() - i + 1));
        }
        return in;
    }
};

#endif /* BIG_NUM_LIB_HPP */
