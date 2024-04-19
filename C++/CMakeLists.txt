cmake_minimum_required(VERSION 3.11.2)

#
#   DSALabs-2024
#   Compile all labs to a single shared library
#
project(DSALabs-2024)

add_library(DSALabs-2024 SHARED
    # Lab 2 sources
    Lab2/include/LinkedList.hpp
    Lab2/include/StaticArrayList.hpp

    # Lab 3 sources
    Lab3/include/DynamicArrayList.hpp
    Lab3/include/CircularDynamicArrayList.hpp
    Lab3/include/LinkedStack.hpp
    Lab3/include/LinkedQueue.hpp
    Lab3/include/ArrayStack.hpp
    
    # Lab 4 sources
    Lab4/include/BinarySearch.hpp
    Lab4/include/InsertionSort.hpp
    Lab4/include/MergeSort.hpp
    Lab4/include/SelectionSort.hpp
    Lab4/include/ArrayMap.hpp

    # Lab 5 sources
    Lab5/include/Numberify.hpp
    Lab5/include/HashFunction.hpp
    Lab5/include/ChainingHashMap.hpp
    Lab5/include/ProbingHashMap.hpp

    # Lab 6 sources
    Lab6/include/BinaryTree.hpp
)

target_include_directories(DSALabs-2024 PUBLIC
    Lab2/include
    Lab3/include
    Lab4/include
    Lab5/include
    Lab6/include
)

set_target_properties(DSALabs-2024 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY build
    LINKER_LANGUAGE CXX
)

#
#   Lab 2 tests
#   Compile lab 2 tests executable
#
project(DSALab2)

add_executable(DSALab2 Lab2/src/test.cpp)

target_include_directories(DSALab2 PUBLIC Lab2/include Testing/include)
target_link_libraries(DSALab2 DSALabs-2024)

set_target_properties(DSALab2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY Lab2/build
)

#
#   Lab 3 tests
#   Compile lab 3 tests executable
#
project(DSALab3)

add_executable(DSALab3 Lab3/src/test.cpp)

target_include_directories(DSALab3 PUBLIC Lab3/include Testing/include)
target_link_libraries(DSALab3 DSALabs-2024)

set_target_properties(DSALab3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY Lab3/build
)

#
#   Lab 4 tests
#   Compile lab 4 tests executable
#
project(DSALab4)

add_executable(DSALab4 Lab4/src/test.cpp)

target_include_directories(DSALab4 PUBLIC Lab4/include Testing/include)
target_link_libraries(DSALab4 DSALabs-2024)

set_target_properties(DSALab4 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY Lab4/build
)

#
#   Lab 5 tests
#   Compile lab 5 tests executable
#
project(DSALab5)

add_executable(DSALab5 Lab5/src/test.cpp)

target_include_directories(DSALab5 PUBLIC Lab5/include Testing/include)
target_link_libraries(DSALab5 DSALabs-2024)

set_target_properties(DSALab5 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY Lab5/build
)

#
#   Lab 6 tests
#   Compile lab 6 tests executable
#
project(DSALab6)

add_executable(DSALab6 Lab6/src/test.cpp)

target_include_directories(DSALab6 PUBLIC Lab6/include Testing/include)
target_link_libraries(DSALab6 DSALabs-2024)

set_target_properties(DSALab6 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY Lab6/build
)