#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
/*
    Box of Static class to ease writing messages to stream
*/

//
namespace Log
{
	enum Color{
	    FG_RED      = 31,
	    FG_GREEN    = 32,
	    FG_YELLOW   = 33,
	    FG_BLUE     = 34,
	    FG_DEFAULT  = 39,
	    BG_RED      = 41,
	    BG_GREEN    = 42,
	    BG_YELLOW    = 43,
	    BG_BLUE     = 44,
	    BG_DEFAULT  = 49
	};
			
	class Error
	{
	public:
	    friend std::ostream& operator<<(std::ostream& os, const Error& error) {
	        return os << "\033[" <<FG_RED <<"m";
	    }
	};
	
	class Debug
	{
	public:
	    friend std::ostream& operator<<(std::ostream& os, const Debug& mod) {
	        return os << "\033[" << FG_DEFAULT << "m";
		}
	};

	class Warn
	{
	public:
	    friend std::ostream& operator<<(std::ostream& os, const Warn& mod) {
	        return os << "\033[" << FG_YELLOW << "mWarning:";
		}
	};

	//singletons to stream output
	static Error s_error;
	static Warn s_warn;
	static Debug s_debug;

	static std::ostream* s_out = &std::cout; //reference to current output stream, default is cout

	
	//Set the log stream
    static void open(std::ostream* out = &std::cout) {
		s_out =out;
	}
    static void close() { 
		*s_out << "\033[" << FG_DEFAULT << "m" << "\033[" << BG_DEFAULT << "m";
	}
 
	
	//Macros to abstract function calls and allow log::error, log::warn streaming!
	//use __FILE__ and __LINE__, to get line where macro was called (text substitution :)
	//#define error error_(__FILE__, __LINE__)
	//#define warn warn_()
	//#define debug debug_() 
	//"Private functions" to be called by macros
	#define error() errorAt(__FILE__, __LINE__)

	static std::ostream& errorAt(const char* filename, int line){
		return *s_out << s_error << "ERROR! at " << filename << ":" <<line << "\n\t";
	}
	static std::ostream& warn() {
		return *s_out << s_warn;
	}
	static std::ostream& debug() {
		return *s_out << s_debug;
	}

}

#endif // LOG_H
