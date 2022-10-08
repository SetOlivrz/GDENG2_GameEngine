#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime(); 

	static double getTimerValue();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&){}
	EngineTime& operator = (EngineTime const&) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;

	static void LogFrameStart();
	static void LogFrameEnd();

	double newVal = 0.3f;
	double ticks = 0.0f;

	bool isSpeeding = true;


	friend class Window;



};

