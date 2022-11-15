/**
 * \file contains implementations of print_ip function.
 */
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

/**
 * \brief A root namespace of the project.
 */
namespace homework {

const char IP_DELIMITER = '.';
const char BYTE_SIZE = 8;

/**
 * \brief Tests that T is of the type std::tuple.
 * 
 * @param <T> a type to be tested
 */
template<class T>
struct is_tuple { };

/**
 * \brief The specialization of is_tuple<T>. The "value" returns "true" if T is a std::tuple and its elements are of the same type.
 * 
 * @param <tuple_first_element>  - a type of a first element in the tuple. 
 *                                 E.g. tuple<short, int, double>. Here the first element is "short".
 * @param <tuple_other_elements> - a parameter pack which contains types of other elements of the tuple.
*                                  E.g. tuple<short, int, double>. Here the other elements are "int, double".
 */
template<typename tuple_first_element, typename...tuple_other_elements>
struct is_tuple<std::tuple<tuple_first_element, tuple_other_elements...>> {
	static const bool value = std::conjunction_v<std::is_same<tuple_first_element, tuple_other_elements>...>;
};

/**
 * \brief Prints the given ip address.
 * 
 * @param ip - the "ip address" as an integral number
 */
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true >
void print_ip(const T& ip) {
	std::size_t number_of_bytes = sizeof(T);
	std::size_t number_of_bits = number_of_bytes * BYTE_SIZE;

	T first_byte_mask = static_cast<T>(0b11111111);

	for (std::size_t i = 0; i < number_of_bytes; ++i) {
		//the mask is used to reset to zero all bytes except the current byte
		T mask = first_byte_mask << (number_of_bits - BYTE_SIZE - i * BYTE_SIZE);
		/*
			apply mask and shift the byte to the right. E.g.:
			"ip"   is 0001 0101 1110 0011
			"mask" is 0000 1111 0000 0000
			The result: 0000 0000 0000 0101
		*/
		T ip_byte = (ip & mask) >> (number_of_bytes - 1 - i) * BYTE_SIZE;

		//1. Cast to an unsigned type because "-1" must be printed as "255". 
		//   It is safe to cast to uint8_t becasue the value cannot be bigger than one byte.
		//2. Without '+' the value will be printed as a character but we need a number.
		std::cout << +static_cast<uint8_t>(ip_byte);
		if (i < number_of_bytes - 1) {
			std::cout << IP_DELIMITER;
		}
	}

	std::cout << std::endl;
}

/**
 * \brief Prints the given ip address.
 * 
 * @param ip - any string
 */
template<typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true >
void print_ip(const T& ip) {
	std::cout << ip << std::endl;
}

/**
 * \brief Prints the given ip address.
 * 
 * @param ip - std::vector<int> or std::list<short>. The container may contain any number of elements.
 */
template<typename T, std::enable_if_t<
	std::disjunction_v<
		std::is_same<T, std::vector<int>>, 
		std::is_same<T, std::list<short>
	>
>, bool> = true >
void print_ip(const T& ip) {
	auto iterator = ip.cbegin();
	for (;;) {
		std::cout << *iterator;
		++iterator;
		if (iterator == ip.cend()) {
			break;
		} else {
			std::cout << IP_DELIMITER;
		}
	}
	std::cout << std::endl;
}

/**
 * \brief Prints a single element of a std::tuple.
 * 
 * @param element 				- an element to be printed
 * @param isLastElement         - if "true", a newline character will be printed after the element.
 *                                If "false", a dot '.' will be printed.
 */
template<typename T>
void print_ip_tuple_element(const T& element, bool isLastElement) {
	std::cout << element;
	if (isLastElement) {
		std::cout << std::endl;
	} else {
		std::cout << IP_DELIMITER;
	}
}

/**
 * \brief Prints the given ip address.
 * 
 * @param <tuple>   - a type of std::tuple with any number of elements.
 * @param <indices> - positions of elements in the tuple. E.g.: 0, 1, 2, 3
 * @param ip		- a std::tuple to be printed
 * @param sequence  - a sequence of indices
 */
template<class tuple, std::size_t... indices>
void print_ip_tuple(const tuple& ip, std::index_sequence<indices...>) {
	//print all elements one by one
	(print_ip_tuple_element(std::get<indices>(ip), (indices == std::tuple_size_v<tuple> - 1)), ...);
}

/**
 * \brief Prints the given ip address.
 * 
 * @param <T> - a type of std::tuple with any number of elements. All elements must be of the same type.
 */
template<typename T, std::enable_if_t<is_tuple<T>::value, bool> = true >
void print_ip(const T& ip) {
	auto seq = std::make_index_sequence<std::tuple_size_v<T>>();
	print_ip_tuple(ip, seq);
}

};