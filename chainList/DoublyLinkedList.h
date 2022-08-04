#pragma once
#include <iostream>
#include "../namespaces.h"
#include "D:\ClionProjects\Data_Structures_And_Algorithms\virtualBaseClassLinearList.h"

using namespace std;
using ExceptionSpace::IllegalParameterValue;

template<class T>
class DoublyLinkedList:public LinearList<T>
{

};