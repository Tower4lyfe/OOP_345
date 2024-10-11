#include "Logger.h"


Logger::Logger() :events(new Event[10]), arrSize(10), elements(0)
{
	
}

Logger::~Logger() 
{
	delete[] events;
}

Logger::Logger(Logger&& log_other)noexcept
{
	events = log_other.events;
	arrSize = log_other.arrSize;
	elements = log_other.elements;
	log_other.events = nullptr;
	log_other.arrSize = 0;
	log_other.elements = 0;
}

Logger& Logger::operator=(Logger&& log_other)noexcept
{
	if (this != &log_other) 
	{
		delete[] events;

		events = log_other.events;
		arrSize = log_other.arrSize;
		elements = log_other.elements;
		log_other.events = nullptr;
		log_other.arrSize = 0;
		log_other.elements = 0;
	}

	return *this;
}

void Logger::addEvent(const Event& event)
{
	if (elements == arrSize) 
	{
		arrSize *= 2;
		Event* newEventArr = new Event[arrSize];

		for (int count = 0; count < elements; ++count) 
		{
			newEventArr[count] = events[count];
		}

		delete[] events;
		events = newEventArr;
	}

	events[elements++] = event;
}

std::ostream& operator<<(std::ostream& os, const Logger& log)
{
	for (int count = 0; count < log.elements; ++count)
	{
		os << log.events[count] << std::endl;
	}

	return os;
}
