#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <optional>
#include <string_view>


class LogDuration
{
  public:
	  explicit LogDuration(const std::string& msg = "")
		  : m_message(msg + ": ")
		  , m_start(std::chrono::steady_clock::now())
	  {}

	~LogDuration() 
	{
		auto finish = std::chrono::steady_clock::now();
		auto dur = finish - m_start;
		std::cerr << m_message
			<< std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
			<< " ms" << std::endl;
	}
private:
	std::string m_message;
	std::chrono::steady_clock::time_point m_start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};
