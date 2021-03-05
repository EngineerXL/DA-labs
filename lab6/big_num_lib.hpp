#ifndef BIG_NUM_LIB_HPP
#define BIG_NUM_LIB_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class TBigNum {
private:
    const int64_t Base = 10;
    const int64_t Radix = 4;
    const int64_t MaxDigit = 1e4;
    std::vector<int64_t> Data;
    size_t NumSize;

    void Normalize() {
        while (Data[NumSize - 1] == 0 and NumSize > 1) {
            Data.pop_back();
            --NumSize;
        }
        std::reverse(Data.begin(), Data.end());
    }

    static void DivMod(const TBigNum & lhs, const TBigNum & rhs, TBigNum & div, TBigNum & mod) {
        if (lhs.NumSize < rhs.NumSize) {
            div.NumSize = 1;
            div.Data.push_back(0);
            mod = lhs;
            return;
        }
        TBigNum res;
        res.NumSize = lhs.NumSize;
        res.Data.resize(res.NumSize);
        TBigNum tmp(rhs.NumSize);
        tmp.Data[tmp.NumSize - 1] = lhs.Data[0];
        TBigNum multDig(2);
        multDig.Data[0] = 1;
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            int64_t l = -1;
            int64_t r = res.MaxDigit;
            TBigNum mid(1);
            while (l + 1 < r) {
                int64_t m = (l + r) / 2;
                mid.Data[0] = m;
                if (mid * rhs > tmp) {
                    r = m;
                } else {
                    l = m;
                }
            }
            res.Data[res.NumSize - i - 1] = l;
            mid.Data[0] = l;
            tmp = (tmp - mid * rhs) * multDig;
            if (i + 1 < lhs.NumSize) {
                tmp.Data[tmp.NumSize - 1] = lhs.Data[i + 1];
            }
        }
        res.Normalize();
        div = res;
        mod = tmp;
    }
public:
    TBigNum() = default;

    TBigNum(const size_t & size) : NumSize(size) {
        Data.resize(NumSize);
    }

    TBigNum(const TBigNum & num) : Data(num.Data), NumSize(num.NumSize) {}

    TBigNum(const std::string & s) {
        size_t n = s.size();
        NumSize = (n + Radix - 1) / Radix;
        Data.resize(NumSize);
        for (size_t i = 0; i < NumSize; ++i) {
            int64_t digit = 0;
            for (int64_t j = 0; j < Radix; ++j) {
                int64_t ind = n - (i + 1) * Radix + j;
                if (ind >= 0ll) {
                    digit = digit * Base + s[ind] - '0';
                }
            }
            Data[NumSize - 1 - i] = digit;
        }
    }

    TBigNum & operator = (const TBigNum & num) {
        Data = num.Data;
        NumSize = num.NumSize;
        return *this;
    }

	friend TBigNum operator + (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.NumSize < rhs.NumSize) {
            return rhs + lhs;
        }
        TBigNum res(lhs.NumSize);
        bool flag = false;
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            int64_t sum;
            if (i > rhs.NumSize - 1) {
                sum = lhs.Data[lhs.NumSize - i - 1];
            } else {
                sum = lhs.Data[lhs.NumSize - i - 1] + rhs.Data[rhs.NumSize - i - 1];
            }
            if (flag) {
                ++sum;
            }
            if (sum >= res.MaxDigit) {
                sum = sum - res.MaxDigit;
                flag = true;
            } else {
                flag = false;
            }
            res.Data[i] = sum;
        }
        if (flag) {
            res.Data.push_back(1);
            ++res.NumSize;
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator - (const TBigNum & lhs, const TBigNum & rhs) {
        TBigNum res(lhs.NumSize);
        bool flag = false;
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            int64_t diff;
            if (i > rhs.NumSize - 1) {
                diff = lhs.Data[lhs.NumSize - i - 1];
            } else {
                diff = lhs.Data[lhs.NumSize - i - 1] - rhs.Data[rhs.NumSize - i - 1];
            }
            if (flag) {
                --diff;
            }
            if (diff < 0) {
                diff = diff + res.MaxDigit;
                flag = true;
            } else {
                flag = false;
            }
            res.Data[i] = diff;
        }
        if (flag) {
            --res.Data[res.NumSize - 1];
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator * (const TBigNum & lhs, const TBigNum & rhs) {
        TBigNum res(lhs.NumSize + rhs.NumSize);
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            for (size_t j = 0; j < rhs.NumSize; ++j) {
                res.Data[i + j] = res.Data[i + j] + lhs.Data[lhs.NumSize - i - 1] * rhs.Data[rhs.NumSize - j - 1];
            }
        }
        for (size_t i = 0; i < lhs.NumSize + rhs.NumSize - 1; ++i) {
            res.Data[i + 1] = res.Data[i + 1] + res.Data[i] / res.MaxDigit;
            res.Data[i] = res.Data[i] % res.MaxDigit;
        }
        res.Normalize();
        return res;
    }

    friend TBigNum operator ^ (TBigNum lhs, TBigNum rhs) {
        TBigNum res(1);
        res.Data[0] = 1;

        TBigNum two(1);
        two.Data[0] = 2;

        while (rhs.NumSize > 0 and rhs.Data[0] > 0) {
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
        if (lhs.NumSize != rhs.NumSize) {
            return lhs.NumSize < rhs.NumSize;
        }
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] < rhs.Data[i];
            }
        }
        return false;
    }

    friend bool operator > (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.NumSize != rhs.NumSize) {
            return lhs.NumSize > rhs.NumSize;
        }
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] > rhs.Data[i];
            }
        }
        return false;
    }

    friend bool operator == (const TBigNum & lhs, const TBigNum & rhs) {
        if (lhs.NumSize != rhs.NumSize) {
            return false;
        }
        for (size_t i = 0; i < lhs.NumSize; ++i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream & operator << (std::ostream & out, const TBigNum & num) {
        out << num.Data[0];
        for (size_t i = 1; i < num.NumSize; ++i) {
            if (num.Data[i] == 0) {
                for (int64_t j = 0; j < num.Radix; ++j) {
                    out << '0';
                }
                continue;
            }
            int64_t curDigit = num.MaxDigit / num.Base;
            while (num.Data[i] / curDigit == 0) {
                out << '0';
                curDigit = curDigit / num.Base;
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
