#ifndef _STRING2HEX_HPP
#define _STRING2HEX_HPP

#include <string>
#include <algorithm>
#include <stdexcept>

std::string string_to_hex(const std::string& input);
std::string hex_to_string(const std::string& input);
char* hex_to_bin(const std::string& input, int *len);

#endif
