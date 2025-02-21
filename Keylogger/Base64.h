#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>

// our encryption will use the base64 algorithm

namespace Base64
{
	std::string base64_encode(const std::string &);

	//// Constants for salting (adding randomness or obfuscation)
	// 3 lines to scramble base64 encoding
	const std::string &SALT1 = "LM::TB::BB";
	const std::string &SALT2 = "_:/_77";
	const std::string &SALT3 = "line=boostedC++";

	// triple encode with base64 with slight modifications (arbitrary)
	std::string EncryptB64(std::string s)
	{
		s = SALT1 + s + SALT2 + SALT3;// Add salts before encoding
		s = base64_encode(s);// First Base64 encode
		s.insert(7, SALT3);	// Insert SALT3 at position 7		
		s += SALT1;	// Append SALT1 to the string
		s = base64_encode(s);// Second Base64 encode
		s = SALT2 + SALT3 + s + SALT1; // Add salts before final encode
		s = base64_encode(s);// Third Base64 encode
		s.insert(1, "Ls");// Insert "Ls" at position 1
		s.insert(7, "A");// Insert "A" at position 7
		return s;// Return the encrypted string
	}

	const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64_encode(const std::string &s)
	{
		std::string ret; // Encoded string result
		int val = 0; // index we use map to table
		int bits = -6; // used to represent number of bits in a subgroup (of six)
		const unsigned int b63 = 0x3F; // decimal value is 63
		// Loop through each character in the input string
		for (const auto &c : s) // auto when type is unknown, c is assign every character from s string
		{
			val = (val << 8) + c; // left binary shift by 8, same as val * 2^8 + c
			bits += 8; // add 8 to numbers of bits when extracting info (octets)
			while (bits >= 0)
			{
				ret.push_back(BASE64_CODES[(val >> bits) & b63]); // does binary right shift + binary AND comparison
				bits -= 6;
			}
		}
		// Handle remaining bits (less than 6) at the end of the string
		if (bits > -6) // means at least one character has been insert
			ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
		// Add padding '=' to make the result length a multiple of 4
		while (ret.size() % 4)
			ret.push_back('=');

		return ret; //return the Base64 encoded string
	}
}

#endif // BASE64_H