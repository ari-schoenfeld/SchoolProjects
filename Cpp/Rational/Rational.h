/*********************

Ari Schoenfeld
CISP 400 - TTH 3:00 pm
Programming Project 3
March 10, 2015

*********************/


#ifndef _RATIONAL_H_
#define _RATIONAL_H_
#include <iostream>
using namespace std;
#include <cstdlib>

class Rational
{
	long long _p;
	long long _q;
	void _reduce();
//private member functions as needed
public:
	Rational ();
	Rational (long long P, long long Q = 1);
	Rational ( const Rational& );

	Rational& operator= (const Rational&);
	Rational& operator+= (const Rational&);
	Rational& operator-= (const Rational&);
	Rational& operator*= (const Rational&);
	Rational& operator/= (const Rational&);
	friend ostream& operator<< (ostream&, const Rational&);
	friend istream& operator>> (istream&, Rational&);
	// operator>> must read what operator<< writes

	Rational operator+ (const Rational&) const; //1
	Rational operator+ (long long) const;
	friend Rational operator+ (long long, const Rational&);
	Rational operator- (const Rational&) const;
	Rational operator- (long long) const;
	friend Rational operator- (long long, const Rational&);
	Rational operator* (const Rational&) const;
	Rational operator* (long long) const;
	friend Rational operator* (long long, const Rational&);
	Rational operator/ (const Rational&) const;
	Rational operator/ (long long) const;
	friend Rational operator/ (long long, const Rational&);
	bool operator== (const Rational&) const; //2 implement this one
	bool operator== (long long) const;
	friend bool operator== (long long, const Rational&);
	bool operator!= (const Rational&) const;
	bool operator!= (long long) const;
	friend bool operator!= (long long, const Rational&);
	bool operator> (const Rational&) const; // implement this one
	bool operator> (long long) const;

	friend bool operator> (long long, const Rational&);
	bool operator< (const Rational&) const;
	bool operator< (long long) const;
	friend bool operator< (long long, const Rational&);
	bool operator>= (const Rational&) const;
	bool operator>= (long long) const;
	friend bool operator>= (long, const Rational&);
	bool operator<= (const Rational&) const;
	bool operator<= (long long) const;
	friend bool operator<= (long long, const Rational&);

	Rational operator++ (int); //post
	Rational operator-- (int); //post
	Rational& operator++ (); //pre
	Rational& operator-- (); //pre
	Rational operator- () const;
	Rational operator+ () const;
	Rational pow( unsigned exp ) const; //returns (*this)exp
	Rational inverse() const;
	// returns the multiplicative inverse of *this;
};
#endif
