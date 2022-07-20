cmake_minimum_required(VERSION 3.22)
project(Data_Structures_And_Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Data_Structures_And_Algorithms main.cpp)

add_executable(selfDefineArray linearList/array/selfDefineArray.cpp linearList/array/myIterator.h linearList/array/illegalParameterValue.h linearList/array/globalFunction.h linearList/array/arrayList.h)