/*
 * coord.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#include "coord.h"

Coord::Coord() :
x(0),
y(0)
{

}

Coord::Coord(double _x, double _y) :
x(_x),
y(_y)
{

}

double Coord::GetX() const
{
	return x;
}

double Coord::GetY() const
{
	return y;
}

void Coord::SetX(const double _x)
{
	x = _x;
}

void Coord::SetY(const double _y)
{
	y = _y;
}

Coord Coord::operator+(const Coord& _coord)
{
	return Coord(x + _coord.GetX(), y + _coord.GetY());
}
