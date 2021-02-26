cmake_minimum_required(VERSION 3.0.0)
project(Lab1Radix VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lab1Radix main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


add_test(UsualWork Lab1Radix 8 15 1234)
set_tests_properties(UsualWork PROPERTIES PASS_REGULAR_EXPRESSION "2E8")

add_test(Zero Lab1Radix 16 32 0)
set_tests_properties(Zero PROPERTIES PASS_REGULAR_EXPRESSION "0")

add_test(NegativeNumber Lab1Radix 6 36 -123452341)
set_tests_properties(NegativeNumber PROPERTIES PASS_REGULAR_EXPRESSION "-1FTFP")

add_test(MaxInt Lab1Radix 10 2 2147483647)
set_tests_properties(MaxInt PROPERTIES PASS_REGULAR_EXPRESSION "1111111111111111111111111111111")

add_test(MaxIntInNotDecimalNotation Lab1Radix 16 2 "7FFFFFFF")
set_tests_properties(MaxIntInNotDecimalNotation PROPERTIES PASS_REGULAR_EXPRESSION "1111111111111111111111111111111")

add_test(MaxIntNegative Lab1Radix 10 2 -2147483648)
set_tests_properties(MaxIntNegative PROPERTIES PASS_REGULAR_EXPRESSION "-10000000000000000000000000000000")

add_test(MaxIntNegativeInNotDecimalNotation Lab1Radix 16 2 "-80000000")
set_tests_properties(MaxIntNegativeInNotDecimalNotation PROPERTIES PASS_REGULAR_EXPRESSION "-10000000000000000000000000000000")

add_test(Overflow Lab1Radix 10 2 2147483648)
set_tests_properties(Overflow PROPERTIES PASS_REGULAR_EXPRESSION "Error while converting number.")

add_test(OverflowInNotDecimalNotation Lab1Radix 35 2 "15V22UN")
set_tests_properties(OverflowInNotDecimalNotation PROPERTIES PASS_REGULAR_EXPRESSION "Error while converting number.")

add_test(TooBigSourceNotation Lab1Radix 38 10 -1239)
set_tests_properties(TooBigSourceNotation PROPERTIES PASS_REGULAR_EXPRESSION "Incorrect source notation.")

add_test(OverflowSourceNotation Lab1Radix 2147483650 10 -1239)
set_tests_properties(OverflowSourceNotation PROPERTIES PASS_REGULAR_EXPRESSION "Incorrect source notation.")

add_test(OverflowDestinationNotation Lab1Radix 35 2147483650 -1239)
set_tests_properties(OverflowDestinationNotation PROPERTIES PASS_REGULAR_EXPRESSION "Incorrect destination notation.")

add_test(DestinationNotationIsNotANumber Lab1Radix 35 !@%^$ -1239)
set_tests_properties(DestinationNotationIsNotANumber PROPERTIES PASS_REGULAR_EXPRESSION "Incorrect arguments.")

add_test(SourceNotationIsNotANumber Lab1Radix $%^%-- 14 -1239)
set_tests_properties(SourceNotationIsNotANumber PROPERTIES PASS_REGULAR_EXPRESSION "Incorrect arguments.")

add_test(InputNumberIsNotInSourceNotation Lab1Radix 11 14 -FE12)
set_tests_properties(InputNumberIsNotInSourceNotation PROPERTIES PASS_REGULAR_EXPRESSION "Error while converting number.")


include(CPack)
