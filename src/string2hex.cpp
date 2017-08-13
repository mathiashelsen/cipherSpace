#include "string2hex.hpp"

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}


std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

char* hex_to_bin(const std::string& input, int *len)
{
	size_t length = input.length();
    if (length & 1) throw std::invalid_argument("odd length");

	char *output = new char[length/2];
	unsigned int j = 0;
	char retVal = 0;
	*len = length/2;
	for( size_t i = 0; i < length; i+= 2)
	{
		std::string byteStr = input.substr(i, 2);
		j = 0;
		retVal = sscanf(byteStr.c_str(), "%x", &j);
		printf("%s : %d, ", byteStr.c_str(), j);
		if( j < 255)
			 output[i/2] = j;
	}

	return output;
}
