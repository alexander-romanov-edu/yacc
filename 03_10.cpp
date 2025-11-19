#include <cassert>
#include <cmath>
#include <compare>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

class Rational
{
public:
    Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        reduce();
    }

    explicit operator double() const
    { 
        return 1.0 * m_num / m_den;
    }

    Rational& operator+=(const Rational& other)
    {
        auto lcm = std::lcm(m_den, other.m_den);
        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;
        reduce();
        return *this;
    }

    Rational& operator-=(const Rational& other)
    { 
        return *this += Rational(-other.m_num, other.m_den);
    }

    Rational& operator*=(const Rational& other)
    {
        m_num *= other.m_num;
        m_den *= other.m_den;
        reduce();
        return *this;
    }

    Rational& operator/=(const Rational& other)
    { 
        return *this *= Rational(other.m_den, other.m_num);
    }

    Rational const operator++(int) { auto x = *this; *this += 1; return x; }
    Rational const operator--(int) { auto x = *this; *this -= 1; return x; }

    Rational& operator++() { *this += 1; return *this; }
    Rational& operator--() { *this -= 1; return *this; }

    friend Rational operator+(Rational lhs, const Rational& rhs) { return lhs += rhs; }
    friend Rational operator-(Rational lhs, const Rational& rhs) { return lhs -= rhs; }
    friend Rational operator*(Rational lhs, const Rational& rhs) { return lhs *= rhs; }
    friend Rational operator/(Rational lhs, const Rational& rhs) { return lhs /= rhs; }

    // Трёхстороннее сравнение
    friend std::strong_ordering operator<=>(const Rational& lhs, const Rational& rhs)
    {
        auto diff = lhs.m_num * rhs.m_den - rhs.m_num * lhs.m_den;
        if (diff < 0) return std::strong_ordering::less;
        if (diff > 0) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    // Равенство через <=> 
    friend bool operator==(const Rational& lhs, const Rational& rhs)
    {
        return (lhs <=> rhs) == 0;
    }

    friend std::istream& operator>>(std::istream& stream, Rational& r)
    {
        return (stream >> r.m_num).ignore() >> r.m_den;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Rational& r)
    {
        return stream << r.m_num << '/' << r.m_den;
    }

private:
    void reduce()
    {
        if (m_den < 0)
        {
            m_num = -m_num;
            m_den = -m_den;
        }
        auto gcd = std::gcd(m_num, m_den);
        m_num /= gcd;
        m_den /= gcd;
    }

    int m_num = 0, m_den = 1;
};

// Функция сравнения double с точностью epsilon
auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    Rational x = 1, y(2, 1);

    std::vector<int> vector_2(5);
    std::vector<int> vector_3 = {1,2,3,4,5};

    assert(equal(static_cast<double>(x), 1));

    assert((x += y) == Rational(3,1));
    assert((x -= y) == Rational(1,1));
    assert((x *= y) == Rational(2,1));
    assert((x /= y) == Rational(1,1));

    assert((x++) == Rational(1,1));
    assert((x--) == Rational(2,1));
    assert((++y) == Rational(3,1));
    assert((--y) == Rational(2,1));

    assert((x + y) == Rational(3,1));
    assert((x - y) == Rational(-1,1));
    assert((x * y) == Rational(2,1));
    assert((x / y) == Rational(1,2));

    assert((x += 1) == Rational(2,1));
    assert((x + 1) == Rational(3,1));
    assert((1 + y) == Rational(3,1));
    assert((1 + 1) == Rational(2,1));

    assert((x < y) == false);
    assert((x > y) == false);
    assert((x <= y) == true);
    assert((x >= y) == true);
    assert((x == y) == true);
    assert((x != y) == false);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;
    stream_1 >> x;
    stream_2 << x;
    assert(stream_2.str() == stream_1.str());
}

