/*
 * coord.h
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#ifndef SRC_WINHANDLING_COORD_H_
#define SRC_WINHANDLING_COORD_H_


class Coord
{
public:
	Coord();
	Coord(double x, double y);

	double GetX() const;
	double GetY() const;

	void SetX(double _x);
	void SetY(double _y);

	Coord operator+(const Coord&);

protected:

private:
	double x;
	double y;
};


#endif /* SRC_WINHANDLING_COORD_H_ */
