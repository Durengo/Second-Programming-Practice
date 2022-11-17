Durlib is an all-purpose C++ library, which I primarily use for all of my projects.

Durlib dependencies:
* fmt
* spdlog
* jsoncpp

Whole of durlib functionality is found in the `DURLIB` namespace.

Durlib functionality:

* Logging - A logger which uses the spdlog library. First initialize the logger with `DURLIB::Log::Init()`, then add and/or use the loggers with macros e.g., `CLI_WARN("text", arguments)`.
* Datemath - An implementation of very primitive date calculations.
* Input:
	* Input - using console to input and return data types.
	* Validation - Parse a string, validate, and return any needed data type.
* Math:
	* Rational:
		* Fraction - basic fraction logic.
* Serialization:
	* Json - incomplete (wrapper) implementation of parsing a json file with the help of the jsoncpp library.

Include durlib with a single header file `durlib.h`.