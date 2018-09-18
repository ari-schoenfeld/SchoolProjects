/*********************

Ari Schoenfeld
CISP 400 - TTH 3:00 pm
Programming Project 3
March 10, 2015

*********************/

#include "Rational.h"

Rational::Rational ()
{
	_p = 0;
	_q = 1;
}
Rational::Rational ( long long p, long long q )
{
	_p = p;
	_q = q;
	_reduce();
}
Rational::Rational ( const Rational& r )
: _p(r._p), _q(r._q) {}

void Rational::_reduce()
{
        if ( _q <= 0 )
        {
                if ( _q == 0 )
                {
                        cout << "Error, division by zero." << endl << "Number is undefined." << endl;
                        cin.get();
                        exit(1);
                }
                else
                {
                        _p *= -1;
                        _q *= -1;
                }
        }
        int small = _q;
        for ( ; small > 0 ; small-- )
        {
                if ( _p%small == 0 && _q%small == 0 )
                {
                        _p /= small;
                        _q /= small;
                        break;
                }
        }
        if ( _p == 0 )
        {
                _q = 1;
        }
}
Rational& Rational::operator= ( const Rational& r )
{
	if (this == &r) return *this;
	_p = r._p;
	_q = r._q;

	return *this;
}
Rational& Rational::operator+= ( const Rational& r )
{
	_p = _p * r._q + _q * r._p;
	_q *= r._q;
	_reduce();

	return *this;
}
Rational& Rational::operator-= ( const Rational& r )
{
        _p = _p * r._q - _q * r._p;
        _q *= r._q;
        _reduce();

        return *this;

}
Rational& Rational::operator*= ( const Rational& r )
{
	_p *= r._p;
	_q *= r._q;
	_reduce();

	return *this;
}
Rational& Rational::operator/= ( const Rational& r )
{
	_p *= r._q;
	_q *= r._p;
	_reduce();

	return *this;
}
ostream& operator<< ( ostream& os, const Rational& r )
{
	os << r._p << ":" << r._q;
	return os;
}
istream& operator>> ( istream& is, Rational& r )
{
	char c;
	long long P,Q;
	is >> P >> c >> Q;
	r = Rational(P,Q);

	return is;
}

Rational Rational::operator+ ( const Rational& r ) const
{
	return Rational(*this).operator+=(r);
}
Rational Rational::operator+ ( long long l ) const
{
	return *this + Rational(l);
}
Rational operator+ (long long l, const Rational& r )
{
	return Rational(l) + r;
}
Rational Rational::operator- ( const Rational& r ) const
{
        return Rational(*this).operator-=(r);
}
Rational Rational::operator- ( long long l ) const
{
        return *this - Rational(l);
}
Rational operator- (long long l, const Rational& r )
{
        return Rational(l) - r;
}
Rational Rational::operator* ( const Rational& r ) const
{
        return Rational(*this).operator*=(r);
}
Rational Rational::operator* ( long long l ) const
{
        return *this * Rational(l);
}
Rational operator* (long long l, const Rational& r )
{
        return Rational(l) * r;
}
Rational Rational::operator/ ( const Rational& r ) const
{
        return Rational(*this).operator/=(r);
}
Rational Rational::operator/ ( long long l ) const
{
        return *this / Rational(l);
}
Rational operator/ (long long l, const Rational& r )
{
        return Rational(l) / r;
}

bool Rational::operator== ( const Rational& r ) const
{
	return _p == r._p && _q == r._q;
}
bool Rational::operator== ( long long l ) const
{
	return *this == Rational(l);
}
bool operator== ( long long l, const Rational& r )
{
	return Rational(l) == r;
}
bool Rational::operator!= ( const Rational& r ) const
{
	return !(*this == r);
}
bool Rational::operator!= ( long long l ) const
{
	return *this != Rational(l);
}
bool operator!= ( long long l, const Rational& r )
{
	return Rational(l) != r;
}
bool Rational::operator> ( const Rational& r ) const
{
	return _p*r._q > _q*r._p;
}
bool Rational::operator> ( long long l ) const
{
	return *this > Rational(l);
}
bool operator> ( long long l, const Rational& r )
{
	return Rational(l) > r;
}
bool Rational::operator< ( const Rational& r ) const
{
	return r > *this;
}
bool Rational::operator< ( long long l ) const
{
	return *this < Rational(l);
}
bool operator< ( long long l, const Rational& r )
{
	return Rational(l) < r;
}
bool Rational::operator>= ( const Rational& r ) const
{
	return (*this > r) || (*this == r);
}
bool Rational::operator>= ( long long l ) const
{
	return *this >= Rational(l);
}
bool operator>= ( long l, const Rational& r )
{
	return Rational(l) >= r;
}
bool Rational::operator<= ( const Rational& r ) const
{
	return (*this < r) || (*this == r);
}
bool Rational::operator<= ( long long l ) const
{
	return *this <= Rational(l);
}
bool operator<= ( long long l, const Rational& r )
{
	return Rational(l) <= r;
}
Rational Rational::operator++ (int) //post
{
	Rational ret(*this);
	operator++();
	return ret;
}
Rational Rational::operator-- (int) //post
{
        Rational ret(*this);
	operator--();
	return ret;
}
Rational& Rational::operator++ () //pre
{
	*this += 1;
	return *this;
}
Rational& Rational::operator-- () //pre
{
        *this += -1;
        return *this;
}

Rational Rational::operator- () const
{
	return -1 * *this;
}
Rational Rational::operator+ () const
{
	return *this;
}
Rational Rational::pow( unsigned exp ) const
{
	if ( exp == 0 ) return Rational( 1, 1 );
	if ( exp == 1 ) return *this;
	if ( exp == 2 ) return *this * *this;
	return *this * pow( exp - 1 );
}
Rational Rational::inverse() const
{
	return Rational(_q, _p);
}
