#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
/*
    Box of Static class to ease writing messages to SDTOUT
*/
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
            return os << "\033[" <<FG_RED <<"m" <<"ERROR! at " << __FILE__ << ":" << __LINE__  << "\n\t";
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
    //singletons to be returned to output
    static Error p_error;
    static Debug p_debug;
    static Warn p_warn;
    static std::ostream* p_out = &std::cout; //reference to current output stream, default is cout

    static void open(std::ostream* out = &std::cout) {p_out =out;}
    static void close() { *Log::p_out << "\033[" << Log::FG_DEFAULT << "m" << "\033[" << Log::BG_DEFAULT << "m";}

}
//qDebug()-like behavior
static std::ostream& error(){return *Log::p_out << Log::p_error;}
static std::ostream& warn() {return *Log::p_out << Log::p_warn;}
static std::ostream& debug() {return *Log::p_out << Log::p_debug;}

#endif // LOG_H
