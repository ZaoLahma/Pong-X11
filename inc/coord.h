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
	Coord(int x, int y);

	int GetX() const;
	int GetY() const;

	void SetX(const int _x);
	void SetY(const int _y);

protected:

private:
	int x;
	int y;
};


#endif /* SRC_WINHANDLING_COORD_H_ */
