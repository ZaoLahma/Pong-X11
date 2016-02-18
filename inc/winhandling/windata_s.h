/*
 * windata_s.h
 *
 *  Created on: Feb 18, 2016
 *      Author: janne
 */

#ifndef INC_WINHANDLING_WINDATA_S_H_
#define INC_WINHANDLING_WINDATA_S_H_

struct WinDataS
{
public:
	Window* winPtr;
	Display* displayPtr;
	uint32_t screenNo;
};

#endif /* INC_WINHANDLING_WINDATA_S_H_ */
