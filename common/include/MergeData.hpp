/*
** EPITECH PROJECT, 2021
** rType
** File description:
** MergeData
*/

#ifndef MERGEDATA_HPP_
#define MERGEDATA_HPP_

#include <cstring>
#include <utility>

class mergeData {
	public:
		template<typename T>
  	static char *mergeBinaries(unsigned char protocol, T elem)
		{
			char *ptr = new char[sizeof(unsigned char) + sizeof(T)];
			std::memcpy(ptr, &protocol, sizeof(unsigned char));
			std::memcpy(&ptr[4], &elem, sizeof(T));
			return ptr;
		}

		template<typename T>
  	static std::pair<unsigned char, T> unPack(char *ptr)
		{
    	return {*(unsigned char*)(ptr), *(T*)(&ptr[4])};
		}

    static unsigned char getProtocol(char *ptr)
		{
    	return *(unsigned char*)(ptr);
		}
};

#endif /* !MERGEDATA_HPP_ */
