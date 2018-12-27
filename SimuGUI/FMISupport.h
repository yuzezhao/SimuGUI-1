#pragma once

#include "InterfaceResponse.h"



class FMISupport {

public:
	InterfaceResponse<bool>* loadFMU(const char*);
};