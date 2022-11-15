#include "ip_printer.h"
#include <gtest/gtest.h>

using namespace std::literals::string_literals;

namespace homework_test {

    template<typename T>
    void test_print_ip_integral(T ip, const std::string& expected) {
        //set up
        testing::internal::CaptureStdout();

        //when
        homework::print_ip(ip);

        //then
        std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ(expected, result);
    }

    template<class T>
    void test_print_ip_container(const T& ip, const std::string& expected) {
        //set up
        testing::internal::CaptureStdout();

        //when
        homework::print_ip(ip);

        //then
        std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ(expected, result);
    }
};

TEST(ip_printer_test, print_ip_int8_negative) {
    homework_test::test_print_ip_integral(int8_t { -1 }, "255\n"s);
}

TEST(ip_printer_test, print_ip_int8_zero) {
    homework_test::test_print_ip_integral(int8_t { 0 }, "0\n"s);
}

TEST(ip_printer_test, print_ip_int8_max) {
    homework_test::test_print_ip_integral(int8_t { 127 }, "127\n"s);
}

TEST(ip_printer_test, print_ip_int16_negative) {
    homework_test::test_print_ip_integral(int16_t { -1 }, "255.255\n"s);
}

TEST(ip_printer_test, print_ip_int16_zero) {
    homework_test::test_print_ip_integral(int16_t { 0 }, "0.0\n"s);
}

TEST(ip_printer_test, print_ip_int16_different_bytes) {
    homework_test::test_print_ip_integral(int16_t { 25919 }, "101.63\n"s);
}

TEST(ip_printer_test, print_ip_int16_max) {
    homework_test::test_print_ip_integral(int16_t { 32767 }, "127.255\n"s);
}

TEST(ip_printer_test, print_ip_int32_negative) {
    homework_test::test_print_ip_integral(int32_t { -1 }, "255.255.255.255\n"s);
}

TEST(ip_printer_test, print_ip_int32_zero) {
    homework_test::test_print_ip_integral(int32_t { 0 }, "0.0.0.0\n"s);
}

TEST(ip_printer_test, print_ip_int32_loopback) {
    homework_test::test_print_ip_integral(int32_t { 2130706433 }, "127.0.0.1\n"s);
}

TEST(ip_printer_test, print_ip_int32_max) {
    homework_test::test_print_ip_integral(int32_t { 2147483647 }, "127.255.255.255\n"s);
}

TEST(ip_printer_test, print_ip_int64_negative) {
    homework_test::test_print_ip_integral(int64_t{ -1 }, "255.255.255.255.255.255.255.255\n"s);
}

TEST(ip_printer_test, print_ip_int64_zero) {
    homework_test::test_print_ip_integral(int64_t{ 0 }, "0.0.0.0.0.0.0.0\n"s);
}

TEST(ip_printer_test, print_ip_int64_different_bytes) {
    homework_test::test_print_ip_integral(int64_t{ 8875824491850138409 }, "123.45.67.89.101.112.131.41\n"s);
}

TEST(ip_printer_test, print_ip_int64_max) {
    homework_test::test_print_ip_integral(int64_t{ 9223372036854775807 }, "127.255.255.255.255.255.255.255\n"s);
}

TEST(ip_printer_test, print_ip_string) {
    //set up
    testing::internal::CaptureStdout();

    //given
    std::string ip = "Hello, World!"s;

    //when
    homework::print_ip(ip);

    //then
    std::string result = testing::internal::GetCapturedStdout();
    ASSERT_EQ(ip + '\n', result);
}

TEST(ip_printer_test, print_ip_vector) {
    homework_test::test_print_ip_container(std::vector<int>{100, 200, 300, 400}, "100.200.300.400\n"s);
}

TEST(ip_printer_test, print_ip_list) {
    homework_test::test_print_ip_container(std::list<short>{400, 300, 200, 100}, "400.300.200.100\n"s);
}

TEST(ip_printer_test, print_ip_tuple) {
    //set up
    testing::internal::CaptureStdout();

    //when
    homework::print_ip(std::make_tuple(123, 456, 789, 0));

    //then
    std::string result = testing::internal::GetCapturedStdout();
    ASSERT_EQ("123.456.789.0\n"s, result);
}