#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

const char IP_DELIMITER = '.';
const char BYTE_SIZE = 8;

template<class T>
struct is_tuple { };

template<typename TupleFirstArg, typename...TupleOtherArgs>
struct is_tuple<std::tuple<TupleFirstArg, TupleOtherArgs...>> {
	static const bool value = std::conjunction_v<std::is_same<TupleFirstArg, TupleOtherArgs>...>;
};

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true >
void print_ip(T ip) {
	std::size_t number_of_bytes = sizeof(T);
	std::size_t number_of_bits = number_of_bytes * BYTE_SIZE;

	T byte_mask = static_cast<T>(0b11111111);

	for (std::size_t i = 0; i < number_of_bytes; ++i) {
		T mask = byte_mask << (number_of_bits - BYTE_SIZE - i * BYTE_SIZE);
		T ip_part = (ip & mask) >> (number_of_bytes - 1 - i) * BYTE_SIZE;

		std::cout << +ip_part;
		if (i < number_of_bytes - 1) {
			std::cout << IP_DELIMITER;
		}
	}
	std::cout << std::endl;
}

template<typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true >
void print_ip(const T& ip) {
	std::cout << ip << std::endl;
}

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
		}
		else {
			std::cout << IP_DELIMITER;
		}
	}
	std::cout << std::endl;
}

template<typename T>
void print_ip_tuple_element(const T& value, std::size_t index, std::size_t tuple_size) {
	std::cout << value;
	if (index < tuple_size - 1) {
		std::cout << IP_DELIMITER;
	}
}

template<class Tuple, std::size_t... index>
void print_ip_tuple(const Tuple& tp, std::index_sequence<index...>) {
	(print_ip_tuple_element(std::get<index>(tp), index, std::tuple_size_v<Tuple>), ...);
}

template<typename T, std::enable_if_t<is_tuple<T>::value, bool> = true >
void print_ip(const T& tp) {
	auto seq = std::make_index_sequence<std::tuple_size_v<T>>();
	print_ip_tuple(tp, seq);
}

int main() {
	print_ip(int8_t{ -1 }); // 255
	print_ip(int16_t{ 0 }); // 0.0
	print_ip(int32_t{ 2130706433 }); // 127.0.0.1
	print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41
	print_ip(std::string{ "Hello, World!" }); // Hello, World!
	print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
	print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
	print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0
	return 0;
}