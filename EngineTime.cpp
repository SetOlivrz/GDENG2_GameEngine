#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

double EngineTime::getTimerValue()
{
	

	if (sharedInstance->ticks >= 3)
	{
		sharedInstance->isSpeeding = !sharedInstance->isSpeeding;
		sharedInstance->ticks = 0;
	}
	
		
	if (sharedInstance->isSpeeding)
	{
		sharedInstance->newVal +=  sharedInstance->deltaTime;
		//std::cout << "speeding: " << sharedInstance->newVal << "\n";

	}
	else
	{
		sharedInstance->newVal -=  sharedInstance->deltaTime;
		//std::cout << "decreasing: " << sharedInstance->newVal << "\n";

	}

	return sharedInstance->newVal/3;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();

	//std::cout << "Frane Update finished in: " << sharedInstance->deltaTime << "\n";

	sharedInstance->ticks += sharedInstance->deltaTime;

}
