#pragma once

#ifndef _RESOLUTION_H_
#define _RESOLUTION_H_

class Resolution
{
public:
	int width = 1280;
	int height = 768;

	Resolution(int _width, int _height): width(_width), height(_height) {}
};

#endif

