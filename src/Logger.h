#ifndef LOGGER_H
#define LOGGER_H

#include <stdexcept>
#include <iostream>

class Logger {
public:
	Logger() = delete;
	~Logger() = delete;

	static void log(const std::string& msg) {

		std::cout << msg << std::endl;
	}

	static void error(const std::string& msg) {

		std::cerr << msg << std::endl;
	}

	template<typename T = std::runtime_error>
	static void fatal(const std::string& errorMsg) {

		error(errorMsg);
		throw T(errorMsg);
	}
};

#define LOG(x) Logger::log(x)
#define ERR(x) Logger::error(x)
#define RUNTIME_ERR(x) Logger::fatal<std::runtime_error>(x)
#define INVALID_ARG(x) Logger::fatal<std::invalid_argument>(x)

#endif // LOGGER_H
