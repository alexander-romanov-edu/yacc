#include <cstdint>
#include <iostream>
#include <array>
#include <format>

class IPv4 {
private:
    std::array<uint8_t, 4> octets{};

    void increment() {
        for (int i = 3; i >= 0; --i) {
            if (octets[i] < 255) {
                ++octets[i];
                return;
            }
            octets[i] = 0;
        }
    }

    void decrement() {
        for (int i = 3; i >= 0; --i) {
            if (octets[i] > 0) {
                --octets[i];
                return;
            }
            octets[i] = 255;
        }
    }

public:
    IPv4() = default;
    IPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
        : octets{a, b, c, d} {}

    // Prefix increment
    IPv4& operator++() {
        increment();
        return *this;
    }

    // Postfix increment
    IPv4 operator++(int) {
        IPv4 temp = *this;
        increment();
        return temp;
    }

    // Prefix decrement
    IPv4& operator--() {
        decrement();
        return *this;
    }

    // Postfix decrement
    IPv4 operator--(int) {
        IPv4 temp = *this;
        decrement();
        return temp;
    }

    // Comparison operators
    friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
        return lhs.octets == rhs.octets;
    }

    friend bool operator!=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
        return lhs.octets < rhs.octets;
    }

    friend bool operator<=(const IPv4& lhs, const IPv4& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const IPv4& lhs, const IPv4& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
        return os << static_cast<int>(ip.octets[0]) << '.'
                  << static_cast<int>(ip.octets[1]) << '.'
                  << static_cast<int>(ip.octets[2]) << '.'
                  << static_cast<int>(ip.octets[3]);
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        int a, b, c, d;
        char dot1, dot2, dot3;
        if (is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d) {
            if (dot1 == '.' && dot2 == '.' && dot3 == '.' &&
                a >= 0 && a <= 255 &&
                b >= 0 && b <= 255 &&
                c >= 0 && c <= 255 &&
                d >= 0 && d <= 255) 
            {
                ip.octets = {static_cast<uint8_t>(a),
                             static_cast<uint8_t>(b),
                             static_cast<uint8_t>(c),
                             static_cast<uint8_t>(d)};
            } else {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }
};


int main() {
    IPv4 ip;
    std::cout << "Enter IP address (a.b.c.d): ";
    std::cin >> ip;

    if (!std::cin) {
        std::cout << "Invalid IP format\n";
        return 1;
    }

    std::cout << "Original IP: " << ip << '\n';
    std::cout << "Prefix increment: " << ++ip << '\n';
    std::cout << "Postfix increment: " << ip++ << '\n';
    std::cout << "After postfix increment: " << ip << '\n';
    std::cout << "Prefix decrement: " << --ip << '\n';
    std::cout << "Postfix decrement: " << ip-- << '\n';
    std::cout << "After postfix decrement: " << ip << '\n';
}
