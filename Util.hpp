#pragma once
#include <string>
#include <vector>

/**
 *  @brief Slices string to integers
 *  @param str String to slice
 *  @param delim Delimiter for slicing
 *  @param parts Vector for storing the result
 *  @return Does not return
 * 
 *  It breaks the @a str into parts and converts them all to ints before appending to @a parts
*/
void split_stoi(const std::string& str, char delim, std::vector<int>& parts);

template<class...>struct types{using type=types;};
template<class T>struct tag{using type=T;};
template<class Tag>using type_t=typename Tag::type;