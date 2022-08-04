cmake_minimum_required(VERSION 3.22)
project(Data_Structures_And_Algorithms)

set(CMAKE_CXX_STANDARD 23)

add_executable(Data_Structures_And_Algorithms main.cpp)
add_executable(selfDefineArray linearList/arrayAndVectorList/selfDefineArray.cpp linearList/arrayAndVectorList/myIterator.h linearList/arrayAndVectorList/globalFunction.h linearList/arrayAndVectorList/arrayList.hpp virtualBaseClassLinearList.h)
add_executable(chainListMain chainList/chainListMain.cpp chainList/chainListMain.h virtualBaseClassLinearList.h D:/ClionProjects/Data_Structures_And_Algorithms/chainList/circularListWithHeader.h chainList/extendedChainList.h chainList/DoublyLinkedList.h)
add_executable(main main.cpp)
add_executable(selectionSort sortAlgorithm/selectionSort.cpp)
add_executable(bubbleSort sortAlgorithm/bubbleSort.cpp)
add_executable(rankSort sortAlgorithm/rankSort.cpp)
add_executable(insertSort sortAlgorithm/insertSort.cpp)