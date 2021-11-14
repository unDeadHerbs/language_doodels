/**
 * APL vector container.
 *
 * This class describes a tree container for floats.
 * There is no coded limitation on the number of nodes on any given level.
 * Element wise operators are also defined.
 */
#ifndef _APL_VECTOR
#define _APL_VECTOR 1
#include "defines.cpp"
#include <iostream>
#include <string>
#include <deque>

class aplvector{
private:
public:
	std::deque<aplvector> below;
	float val;
	bool isbase()const;
	aplvector();
	aplvector(float);
	aplvector(std::string);
	aplvector(const aplvector&);
	void join(float);
	void join(aplvector);
	void append(float);
	void append(aplvector);

	aplvector operator+=(const aplvector&);
	aplvector operator-=(const aplvector&);
	aplvector operator*=(const aplvector&);
	aplvector operator/=(const aplvector&);

	aplvector operator+(const aplvector&)const;
	aplvector operator-(const aplvector&)const;
	aplvector operator*(const aplvector&)const;
	aplvector operator/(const aplvector&)const;

	aplvector operator+=(const float&);
	aplvector operator-=(const float&);
	aplvector operator*=(const float&);
	aplvector operator/=(const float&);

	aplvector inv(const int&);

	friend aplvector operator+(const aplvector&,const int&);
	friend aplvector operator-(const aplvector&,const int&);
	friend aplvector operator*(const aplvector&,const int&);
	friend aplvector operator/(const aplvector&,const int&);
	friend aplvector operator/(const int&,const aplvector&);
	friend aplvector operator+(const int&,const aplvector&);
	friend aplvector operator-(const int&,const aplvector&);
	friend aplvector operator*(const int&,const aplvector&);

	aplvector& operator[](int);

	int depth()const;

	void print();

	void display(std::ostream&,std::string=" ",std::string="\n");
};
#endif
