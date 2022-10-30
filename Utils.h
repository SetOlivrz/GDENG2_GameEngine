#pragma once
#include <time.h>
#include <stdlib.h>
class Utils
{
public:
	// addition
	static void addArr3(float a[], float b[], float sum[])
	{
		for (size_t i = 0; i < 3; i++)
		{
			sum[i] = b[i]+ a[i];
		}
	}
	// copy
	static void copyArr3(float a[], float b[])
	{
		for (size_t i = 0; i < 3; i++)
		{
			b[i] = a[i];
		}
	}
	// checker
	static bool isEqual(float a[], float b[])
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}

	// reset
	static void resetArr3(float arr[])
	{
		for (size_t i = 0; i < 3; i++)
		{
			arr[i] = 0;
		}
	}

	// subtract
	static void subArr3(float a[], float b[], float sum[])
	{
		for (size_t i = 0; i < 3; i++)
		{
			sum[i] = b[i] - a[i];
		}
	}

	static float randFloat()
	{
		return ((float)rand()) / ((float)RAND_MAX);
	}

	static float randFloatInterval(float min, float max)
	{
		return randFloat() * (max - min) + min;
	}

	static float radToDeg(float radian)
	{
		double pi = 3.14159;
		return(radian * (180 / pi));
	}
	static float degToRad(float degree)
	{
		double pi = 3.14159265359;
		return (degree * (pi / 180));
	}
};

