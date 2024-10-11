#ifndef LOGGER_H
#define LOGGER_H

#include "event.h"


class Logger
{
	Event* events;
	int arrSize;
	int elements;

public:
	Logger();
	~Logger();

	Logger(Logger&& log_other) noexcept;
	Logger& operator = (Logger&& log_other) noexcept;

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void addEvent(const Event& event);
	friend std::ostream& operator <<(std::ostream& os, const Logger& log);

};

#endif
