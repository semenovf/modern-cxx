#include <iostream>

using namespace std;

/**
 * @brief Class represents a two part of number, where first - real number (real axis), second - image number (image axis)
 * @param real part - real axis
 * @param image part - image axis
 * @author KomulovReal axis A.V.
 * @details contact: crashc@yandex.ru
 * @headerfile complex.h
 */

template< typename T >
class Complex
{
public:
    Complex<T>()
    {};

    Complex<T>(const T real = T(0), const T image = T(0))
        : m_re(real), m_im(image)
    {};

    Complex<T>(const Complex<T>& compNum)
        : m_re(compNum.m_re), m_im(compNum.m_im)
    {};

    constexpr T re() const
    {
        return m_re;
    }

    constexpr T im() const
    {
        return m_im;
    }

    Complex<T> operator +() const; ///< unary operator
    Complex<T> operator -() const; ///< unary operator

    Complex<T>& operator +=(const Complex<T>&);
    Complex<T>& operator -=(const Complex<T>&);
    Complex<T>& operator *=(const Complex<T>&);
    Complex<T>& operator /=(const Complex<T>&);

    Complex<T> operator+(const Complex<T>&) const;
    Complex<T> operator-(const Complex<T>&) const;
    Complex<T> operator*(const Complex<T>&) const;
    Complex<T> operator/(const Complex<T>&) const;

    template<typename U>
    friend std::ostream& operator <<(std::ostream& stream, const Complex<U>&);

    template<typename U>
    friend std::istream& operator >>(std::ostream& stream, const Complex<U>&);

    private:
        T m_re = T(0);
        T m_im = T(0);
};

///< Transcendentals:
template<typename T>
    inline T
    abs(const Complex<T>& number)
{
    T x = number.re();
    T y = number.im();
    const T t = std::max(std::abs(x), std::abs(y));
    if(t == T())
        return t;
    x /= t;
    y /= t;
    return t * sqrt(x*x+y*y);
}

template<typename T>
Complex<T> Complex<T>::operator +() const
{
    return Complex(-m_re, -m_im);
}

template<typename T>
Complex<T> Complex<T>::operator -() const
{
    return Complex(-m_re, -m_im);
}

template<typename T>
Complex<T>& Complex<T>::operator +=(const Complex<T>& compNum2)
{
    m_re += compNum2.m_re;
    m_im += compNum2.m_im;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator -=(const Complex<T>& compNum2)
{
    m_re -= compNum2.m_re;
    m_im -= compNum2.m_im;
    return * this;
}

template<typename T>
Complex<T>& Complex<T>::operator *=(const Complex<T>& compNum2) {
    T real = m_re * compNum2.m_re - m_im * compNum2.m_im;
    T imag = m_re * compNum2.m_im + m_im * compNum2.m_re;
    m_re = real;
    m_im = imag;
    return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator/=(const Complex<T>& compNum2)
{
    Complex<T> del = Complex<T>(*this) * Complex<T>(compNum2.re(), -compNum2.im());
    T denominator = compNum2.re()* compNum2.re() + compNum2.im() * compNum2.im();
    m_re = del.re()/denominator;
    m_im = del.im()/denominator;
    return *this;
}

template<typename T>
Complex<T> Complex<T>::operator+(const Complex<T>& compNum2) const
{
    return Complex<T>(*this) += compNum2;
}

template<typename T>
Complex<T> Complex<T>::operator-(const Complex<T>& compNum2) const
{
    return Complex<T>(*this) -= compNum2;
}

template<typename T>
Complex<T> Complex<T>::operator*(const Complex<T>& compNum2) const
{
    return Complex<T>(*this) *= compNum2;
}

template<typename T>
Complex<T> Complex<T>::operator/(const Complex<T>& compNum2) const
{
    return Complex<T>(*this) /= compNum2;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& c)
{
    os << c.im();
    if (c.im() < 0)
        os << c.im() << "i";
    else if (c.im() > 0)
        os << "+" << c.im() << "i";
    return os;
}

template<typename U>
std::istream& operator >>(std::ostream& stream, const Complex<U>&)
{
  //TODO
}
