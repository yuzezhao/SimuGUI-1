#pragma once

/*
* ≈‰÷√¿‡
* @date : 2018/09/24
* @author : jihang
*/

#include <vector>

#include "RTI.hh"

using namespace std;

class ObjectClassSet {
public:
	string className;
	vector<string> attributeList;
	RTI::ObjectClassHandle classHandle;
	vector<RTI::AttributeHandle> handleList;
};