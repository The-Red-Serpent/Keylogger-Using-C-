#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

namespace Helper
{
    // This declares a template function ToString, which converts any type T into a string
    template <class T> 
    std::string  ToString(const T &); 

    struct DateTime
    {
        DateTime() // Default constructor for DateTime class
        {
            time_t ms;  // Declare a variable of type time_t to hold the raw timestamp
 
            time (&ms); // Get the current time (in seconds since the Unix epoch) and store it in ms

            struct tm *info = localtime(&ms); // Convert the raw timestamp to local time and store it in a struct tm

            D = info->tm_mday; // Assign the day of the month from the struct tm (tm_mday) to the member variable D
            m= info->tm_mon; // Assign the month (tm_mon is 0-based, so January is 0, February is 1, etc.) to m
            y=1900+info->tm_year; // Assign the year to y. tm_year is years since 1900, so we add 1900
            M = info->tm_min; // Assign the minute (tm_min) to M
            H = info->tm_hour; // Assign the hour (tm_hour) to H
            S = info->tm_sec; // Assign the second (tm_sec) to S
        } 

        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y),  H(H), M(M), S(S) {} //This constructor allows you to create a DateTime object by specifying both the date and the time.
        DateTime(int D, int m, int y) : D(D), m(m), y(y),  H(0), M(0), S(0) {} //This constructor allows you to create a DateTime object by specifying only the date (day, month, year), and it defaults the time to midnight (00:00:00).

        DateTime Now() const // The Now() function in the DateTime struct is a member function that returns the current date and time as a DateTime object.
        {
            return DateTime();

        }
        int D,m,y,H,M,S;
         // This function returns the date part of the DateTime object as a formatted string in the format: "dd.mm.yyyy".
        std::string GetDateString()  const
        {
            return std::string(D < 10 ? "0" : "" )  + ToString(D)+ std::string(m <10 ? ".0" : ".") + ToString (m) + "." + ToString(y);
        }

        // This function returns the time part of the DateTime object as a formatted string in the format: "hh:mm:ss". It accepts an optional separator (sep) to customize the separator between hours, minutes, and seconds.
        std::string GetTimeString(const std::string &sep = ":") const
        {
                return std::string (H < 10 ? "0" : "")+ ToString(H)+sep+std::string(M < 10 ? "0":"")+ToString(M)+sep+ std::string(S<10?sep:"")+ToString(S);

        }

        //This function combines the date and time parts of the DateTime object into a single string, formatted as "dd.mm.yyyy hh:mm:ss".
        std::string GetDateTimeString( const std::string &sep=":") const
        {
            return GetDateString() + " " + GetTimeString(sep);
        } 
    };

    template <class  T>

    std::string ToString(const T &e)
    //  generic function that converts an object of any type T into its string representation using an ostringstream
    {
        // std::ostringstream is useful when you need to build a string from different pieces of data (such as integers, floating-point numbers, or even user-defined objects).
        std::ostringstream s;
        s << e; // The << operator is used to send data into the stream
        return s.str(); // oss.str() retrieves the contents of the stream as a string
    }

    void WriteAppLog(const std::string &s)
    {
    // Open the file in append mode
    std::ofstream file("AppLog.txt", std::ios::app); // app stands for append file

    // Write the timestamp and the log message to the file
    // std::ios::app is a flag that tells the program to append new content to the end of the file, instead of replacing what's already there.
    file << "[" << Helper::DateTime().GetDateTimeString() << "]" << "\n" << s << std::endl << "\n";

    // Close the file after writing
    file.close();
    }

}
#endif