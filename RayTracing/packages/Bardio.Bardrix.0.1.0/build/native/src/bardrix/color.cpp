//
// Created by Bardio on 29/03/2024.
//

#include <bardrix/color.h>

namespace bardrix {

    // Constructors

    color::color(unsigned int rgba) : c_union_{ rgba } {}

    color::color(color::uchar r, color::uchar g, color::uchar b, color::uchar a) : c_union_{ r, g, b, a } {}

    // Getters/Setter

    color::uchar color::r() const noexcept { return c_union_.r_g_b_a.r; }

    color::uchar color::g() const noexcept { return c_union_.r_g_b_a.g; }

    color::uchar color::b() const noexcept { return c_union_.r_g_b_a.b; }

    color::uchar color::a() const noexcept { return c_union_.r_g_b_a.a; }

    void color::r(color::uchar r) noexcept { c_union_.r_g_b_a.r = r; }

    void color::g(color::uchar g) noexcept { c_union_.r_g_b_a.g = g; }

    void color::b(color::uchar b) noexcept { c_union_.r_g_b_a.b = b; }

    void color::a(color::uchar a) noexcept { c_union_.r_g_b_a.a = a; }

    unsigned color::rgba() const noexcept { return c_union_.rgba; }

    void color::rgba(unsigned int rgba) noexcept { c_union_.rgba = rgba; }

    // Methods

    color& color::invert() noexcept {
        return *this = ~*this;
    }

    color color::inverted() const noexcept {
        return ~*this;
    }

    color& color::grayscale() noexcept {
        // Grayscale formula: 0.299 * R + 0.587 * G + 0.114 * B
        auto gray = static_cast<color::uchar>(std::round(0.299 * c_union_.r_g_b_a.r + 0.587 * c_union_.r_g_b_a.g + 0.114 * c_union_.r_g_b_a.b));
        c_union_.r_g_b_a.r = gray;
        c_union_.r_g_b_a.g = gray;
        c_union_.r_g_b_a.b = gray;
        return *this;
    }

    color color::grayscaled() const noexcept {
        // Grayscale formula: 0.299 * R + 0.587 * G + 0.114 * B
        color gray = *this;
        gray.grayscale();
        return gray;
    }

    // Operators

    color color::operator+(const color& other) const noexcept {
        color result = *this;
        result += other;
        return result;
    }

    color color::operator+(color::uchar scalar) const noexcept {
        color result = *this;
        result += scalar;
        return result;
    }

    color operator+(color::uchar scalar, const color& color) noexcept {
        return color + scalar;
    }

    color& color::operator+=(const color& other) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r <= UCHAR_MAX - other.c_union_.r_g_b_a.r ? c_union_.r_g_b_a.r +
                                                                                          other.c_union_.r_g_b_a.r
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g <= UCHAR_MAX - other.c_union_.r_g_b_a.g ? c_union_.r_g_b_a.g +
                                                                                          other.c_union_.r_g_b_a.g
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b <= UCHAR_MAX - other.c_union_.r_g_b_a.b ? c_union_.r_g_b_a.b +
                                                                                          other.c_union_.r_g_b_a.b
                                                                                        : UCHAR_MAX;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a <= UCHAR_MAX - other.c_union_.r_g_b_a.a ? c_union_.r_g_b_a.a +
                                                                                          other.c_union_.r_g_b_a.a
                                                                                        : UCHAR_MAX;
        return *this;
    }

    color& color::operator+=(color::uchar scalar) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.r + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.g + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.b + scalar : UCHAR_MAX;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a <= UCHAR_MAX - scalar ? c_union_.r_g_b_a.a + scalar : UCHAR_MAX;
        return *this;
    }

    color color::operator-(const color& other) const noexcept {
        color result = *this;
        result -= other;
        return result;
    }

    color color::operator-(color::uchar scalar) const noexcept {
        color result = *this;
        result -= scalar;
        return result;
    }

    color operator-(color::uchar scalar, const color& color) noexcept {
        return { static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.r ? scalar - color.c_union_.r_g_b_a.r : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.g ? scalar - color.c_union_.r_g_b_a.g : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.b ? scalar - color.c_union_.r_g_b_a.b : 0),
                 static_cast<color::uchar>(scalar >= color.c_union_.r_g_b_a.a ? scalar - color.c_union_.r_g_b_a.a
                                                                              : 0) };
    }

    color& color::operator-=(const color& other) noexcept {
        c_union_.r_g_b_a.r =
                c_union_.r_g_b_a.r >= other.c_union_.r_g_b_a.r ? c_union_.r_g_b_a.r - other.c_union_.r_g_b_a.r : 0;
        c_union_.r_g_b_a.g =
                c_union_.r_g_b_a.g >= other.c_union_.r_g_b_a.g ? c_union_.r_g_b_a.g - other.c_union_.r_g_b_a.g : 0;
        c_union_.r_g_b_a.b =
                c_union_.r_g_b_a.b >= other.c_union_.r_g_b_a.b ? c_union_.r_g_b_a.b - other.c_union_.r_g_b_a.b : 0;
        c_union_.r_g_b_a.a =
                c_union_.r_g_b_a.a >= other.c_union_.r_g_b_a.a ? c_union_.r_g_b_a.a - other.c_union_.r_g_b_a.a : 0;
        return *this;
    }

    color& color::operator-=(color::uchar scalar) noexcept {
        c_union_.r_g_b_a.r = c_union_.r_g_b_a.r >= scalar ? c_union_.r_g_b_a.r - scalar : 0;
        c_union_.r_g_b_a.g = c_union_.r_g_b_a.g >= scalar ? c_union_.r_g_b_a.g - scalar : 0;
        c_union_.r_g_b_a.b = c_union_.r_g_b_a.b >= scalar ? c_union_.r_g_b_a.b - scalar : 0;
        c_union_.r_g_b_a.a = c_union_.r_g_b_a.a >= scalar ? c_union_.r_g_b_a.a - scalar : 0;
        return *this;
    }

    color color::operator*(const double scalar) const noexcept {
        color result = *this;
        result *= scalar;
        return result;
    }

    color operator*(const double scalar, const color& color) noexcept {
        return color * scalar;
    }

    color& color::operator*=(const double scalar) noexcept {
        if (less_than_or_nearly_equal(scalar, 0))
            this->c_union_ = { 0, 0, 0, 0 };

        c_union_.r_g_b_a.r = static_cast<color::uchar>(c_union_.r_g_b_a.r * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.r *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.g = static_cast<color::uchar>(c_union_.r_g_b_a.g * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.g *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.b = static_cast<color::uchar>(c_union_.r_g_b_a.b * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.b *
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.a = static_cast<color::uchar>(c_union_.r_g_b_a.a * scalar <= UCHAR_MAX ? c_union_.r_g_b_a.a *
                                                                                                  scalar : UCHAR_MAX);
        return *this;
    }

    color color::operator/(const double scalar) const {
        color result = *this;
        result /= scalar;
        return result;
    }

    color operator/(const double scalar, const color& color) {
        if (color.r() == 0 || color.g() == 0 || color.b() == 0 || color.a() == 0)
            throw std::invalid_argument("Division by zero");
        if (scalar < 0)
            throw std::invalid_argument("Division by negative number");

        return { static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.r <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.r
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.g <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.g
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.b <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.b
                                                                                          : UCHAR_MAX),
                 static_cast<color::uchar>(scalar / color.c_union_.r_g_b_a.a <= UCHAR_MAX ? scalar /
                                                                                            color.c_union_.r_g_b_a.a
                                                                                          : UCHAR_MAX) };
    }

    color& color::operator/=(const double scalar) {
        if (nearly_equal(scalar, 0))
            throw std::invalid_argument("Division by zero");
        if (scalar < 0)
            throw std::invalid_argument("Division by negative number");

        c_union_.r_g_b_a.r = static_cast<color::uchar>(c_union_.r_g_b_a.r / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.r /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.g = static_cast<color::uchar>(c_union_.r_g_b_a.g / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.g /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.b = static_cast<color::uchar>(c_union_.r_g_b_a.b / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.b /
                                                                                                  scalar : UCHAR_MAX);
        c_union_.r_g_b_a.a = static_cast<color::uchar>(c_union_.r_g_b_a.a / scalar <= UCHAR_MAX ? c_union_.r_g_b_a.a /
                                                                                                  scalar : UCHAR_MAX);
        return *this;
    }

    color color::operator%(color::uchar scalar) const {
        if (scalar == 0)
            throw std::invalid_argument("Division by zero");

        color result = *this;
        result %= scalar;
        return result;
    }

    color operator%(color::uchar scalar, const color& color) {
        if (color.r() == 0 || color.g() == 0 || color.b() == 0 || color.a() == 0)
            throw std::invalid_argument("Division by zero");

        return { static_cast<color::uchar>(scalar % color.c_union_.r_g_b_a.r),
                 static_cast<color::uchar>(scalar % color.c_union_.r_g_b_a.g),
                 static_cast<color::uchar>(scalar % color.c_union_.r_g_b_a.b),
                 static_cast<color::uchar>(scalar % color.c_union_.r_g_b_a.a) };
    }

    color& color::operator%=(color::uchar scalar) {
        if (scalar == 0)
            throw std::invalid_argument("Division by zero");

        c_union_.r_g_b_a.r %= scalar;
        c_union_.r_g_b_a.g %= scalar;
        c_union_.r_g_b_a.b %= scalar;
        c_union_.r_g_b_a.a %= scalar;
        return *this;
    }

    color color::operator~() const noexcept {
        return color(c_union_.rgba ^ 0x00FFFFFF);
    }

    bool color::operator==(const color& other) const noexcept {
        return c_union_.r_g_b_a.r == other.c_union_.r_g_b_a.r && c_union_.r_g_b_a.g == other.c_union_.r_g_b_a.g &&
               c_union_.r_g_b_a.b == other.c_union_.r_g_b_a.b && c_union_.r_g_b_a.a == other.c_union_.r_g_b_a.a;
    }

    bool color::operator!=(const color& other) const noexcept {
        return !(*this == other);
    }

    bool color::operator<(const color& other) const noexcept {
        return c_union_.rgba < other.c_union_.rgba;
    }

    bool color::operator<=(const color& other) const noexcept {
        return c_union_.rgba <= other.c_union_.rgba;
    }

    bool color::operator>(const color& other) const noexcept {
        return c_union_.rgba > other.c_union_.rgba;
    }

    bool color::operator>=(const color& other) const noexcept {
        return c_union_.rgba >= other.c_union_.rgba;
    }

    std::ostream& color::print(std::ostream& os) const noexcept {
     return os << "(" << static_cast<int>(c_union_.r_g_b_a.r) << ", " << static_cast<int>(c_union_.r_g_b_a.g)
               << ", " << static_cast<int>(c_union_.r_g_b_a.b) << ", " << static_cast<int>(c_union_.r_g_b_a.a) << ")";
    }

    std::ostream& operator<<(std::ostream& os, const color& color) noexcept {
        return color.print(os);
    }

} // bardrix