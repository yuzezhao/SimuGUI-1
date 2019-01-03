#pragma once

#include "fmi2.h"

#include "InterfaceResponse.h"

#define FMI_MODEL_EXCHANGE 1
#define FMI_COSIMULATION 2

class FMISupport {

public:
	InterfaceResponse<bool>* loadFMU(const char*, int);
	void unLoad();
	InterfaceResponse<bool>* simulateByCs(double, double, double, fmi2Boolean, char, int, char **);

private:
	bool loadDll(const char*);
	void *getAdr(bool*, HMODULE, const char*);

public:
	FMU fmu;
	int type;
	Component *component;

private:
	char* currentDir;
};

void fmuLogger(void*, fmi2String, fmi2Status, fmi2String, fmi2String, ...);
void replaceRefsInMessage(const char*, char*, int, FMU*);
ScalarVariable* getSV(FMU*, char, fmi2ValueReference);
const char* fmi2StatusToString(fmi2Status);