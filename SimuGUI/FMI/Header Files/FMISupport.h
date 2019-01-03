#pragma once

#include <QObject>
#include <fstream>

#include "fmi2.h"

#define FMI_MODEL_EXCHANGE 1
#define FMI_COSIMULATION 2

using namespace std;

class FMISupport : public QObject {

	Q_OBJECT

public:
	explicit FMISupport(QObject *parent = NULL);
	virtual ~FMISupport() {};

public:
	bool loadFMU(const char*, int);
	void unLoad();
	bool simulateByCs(double, double, double, int, char **);
	bool simulateByMe(double, double, double, int, char **);

private:
	bool loadDll(const char*);
	void *getAdr(bool*, HMODULE, const char*);
	void outputData(ofstream&, double, bool);

private:
	char* currentDir;
	FMU fmu;
	int type;
	fmi2Component c;

signals:
	void postUIMsg(QString);
};

void fmuLogger(void*, fmi2String, fmi2Status, fmi2String, fmi2String, ...);
void replaceRefsInMessage(const char*, char*, int, FMU*);
ScalarVariable* getSV(FMU*, char, fmi2ValueReference);
const char* fmi2StatusToString(fmi2Status);