
#ifdef WIN32
#include <direct.h>    
#define GetCurrentDir _getcwd
#else    
#include <unistd.h>    
#define GetCurrentDir getcwd 
#endif

#include <sstream>

#include "FMISupport.h"
#include "xmlVersionParser.h"

#define DIRECTORY_PATH_SIZE 1024
static char currentDirectory[DIRECTORY_PATH_SIZE];
#define UNZIP_CMD ".\\FMIpackage\\7z\\7z x -aoa -o"
// -x   Extracts files from an archive with their full paths in the current dir, or in an output dir if specified
// -aoa Overwrite All existing files without prompt
// -o   Specifies a destination directory where files are to be extracted
#define OUT_PATH "\\FMIpackage\\tmp\\"

#define SEVEN_ZIP_NO_ERROR 0
#define SEVEN_ZIP_WARNING 1
#define SEVEN_ZIP_ERROR 2
#define SEVEN_ZIP_COMMAND_LINE_ERROR 7
#define SEVEN_ZIP_OUT_OF_MEMORY 8
#define SEVEN_ZIP_STOPPED_BY_USER 255

#ifdef _WIN64
#define DLL_DIR   "binaries\\win64\\"
#else
#define DLL_DIR   "binaries\\win32\\"
#endif

InterfaceResponse<bool>* FMISupport::loadFMU(const char *filePath, int simuType) {
	string resultMsg;
	type = simuType;

	//获取当前目录
	currentDir = GetCurrentDir(currentDirectory, DIRECTORY_PATH_SIZE);
	ostringstream ss;
	string str;

	//写控制流
	ss << UNZIP_CMD << "\"" << currentDir << OUT_PATH << "\" \"" << filePath << "\" > NUL";
	str = ss.str();
	//解压缩
	int code = system(str.c_str());
	switch (code) {
	case SEVEN_ZIP_NO_ERROR: break;
	case SEVEN_ZIP_WARNING: return InterfaceResponse<bool>::createByErrorMessage("warning");
	case SEVEN_ZIP_ERROR: return InterfaceResponse<bool>::createByErrorMessage("error");
	case SEVEN_ZIP_COMMAND_LINE_ERROR: return InterfaceResponse<bool>::createByErrorMessage("command line error");
	case SEVEN_ZIP_OUT_OF_MEMORY: return InterfaceResponse<bool>::createByErrorMessage("out of memory");
	case SEVEN_ZIP_STOPPED_BY_USER: return InterfaceResponse<bool>::createByErrorMessage("stopped by user");
	default: return InterfaceResponse<bool>::createByErrorMessage("unknown problem");
	}
	//resultMsg += "unzip success!\n";

	//判断版本是否符合要求
	ss.clear();
	ss.str("");
	ss << currentDir << OUT_PATH << "modelDescription.xml";
	str = ss.str();//str里存着xml描述

	//TODO:注掉了一句关闭xml的话
	char *xmlFmiVersion = extractVersion(str.c_str());

	if (xmlFmiVersion == NULL) {
		return InterfaceResponse<bool>::createByErrorMessage("The FMI version of the FMU could not be read");
	}
	if (strcmp(xmlFmiVersion, fmi2Version) != 0) {
		return InterfaceResponse<bool>::createByErrorMessage("The FMI version wrong");
	}
	//resultMsg += "version check success!\n";

	//提取模型描述并输出
	char* xmlPath = new char[str.length() + 1];
	strcpy(xmlPath, str.c_str());

	//TODO:注掉了一句关闭xml的话
	fmu.modelDescription = parse(xmlPath);

	//解析模型描述
	Element* e = (Element*)(fmu.modelDescription);
	int n;
	const char **attributes = getAttributesAsArray(e, &n);
	if (!attributes) {
		return InterfaceResponse<bool>::createByErrorMessage("ModelDescription printing aborted.");
	}
	resultMsg = resultMsg + getElementTypeName(e) + "\n";
	for (int i = 0; i < n; i += 2) {
		resultMsg = resultMsg + attributes[i] + " = " + attributes[i + 1] + "\n";
	}
	if (type == FMI_MODEL_EXCHANGE) {
		component = getModelExchange(fmu.modelDescription);
		if (!component) {
			return InterfaceResponse<bool>::createByErrorMessage(
				"error: No ModelExchange element found in model description. This FMU is not for Model Exchange.");
		}
	}
	else if (type == FMI_COSIMULATION) {
		component = getCoSimulation(fmu.modelDescription);
		if (!component) {
			return InterfaceResponse<bool>::createByErrorMessage(
				"error: No CoSimulation element found in model description. This FMU is not for Co-Simulation.");
		}
	}
	resultMsg = resultMsg + getElementTypeName((Element*)component) + "\n";
	attributes = getAttributesAsArray((Element *)component, &n);
	if (!attributes) {
		return InterfaceResponse<bool>::createByErrorMessage("ModelDescription printing aborted 2.");
	}
	for (int i = 0; i < n; i += 2) {
		resultMsg = resultMsg + attributes[i] + " = " + attributes[i + 1] + "\n";
	}
	//获取modelID
	const char *modelId;
	if (type == FMI_MODEL_EXCHANGE) {
		modelId = getAttributeValue((Element *)getModelExchange(fmu.modelDescription), att_modelIdentifier);
	}
	else if (type == FMI_COSIMULATION) {
		modelId = getAttributeValue((Element *)getCoSimulation(fmu.modelDescription), att_modelIdentifier);
	}

	//加载dll功能
	ss.clear();
	ss.str("");
	ss << currentDir << OUT_PATH << DLL_DIR << modelId << ".dll";
	str = ss.str();

	if (!loadDll(str.c_str())) {
		return InterfaceResponse<bool>::createByErrorMessage("load dll error");
	}
	return InterfaceResponse<bool>::createBySuccessMessage(resultMsg);
}

bool FMISupport::loadDll(const char* dllPath) {
	bool s = true;

	HMODULE h = LoadLibrary(dllPath);

	if (!h) {
		return false;
	}
	fmu.dllHandle = h;
	fmu.getTypesPlatform = (fmi2GetTypesPlatformTYPE *)getAdr(&s, h, "fmi2GetTypesPlatform");
	fmu.getVersion = (fmi2GetVersionTYPE *)getAdr(&s, h, "fmi2GetVersion");
	fmu.setDebugLogging = (fmi2SetDebugLoggingTYPE *)getAdr(&s, h, "fmi2SetDebugLogging");
	fmu.instantiate = (fmi2InstantiateTYPE *)getAdr(&s, h, "fmi2Instantiate");
	fmu.freeInstance = (fmi2FreeInstanceTYPE *)getAdr(&s, h, "fmi2FreeInstance");
	fmu.setupExperiment = (fmi2SetupExperimentTYPE *)getAdr(&s, h, "fmi2SetupExperiment");
	fmu.enterInitializationMode = (fmi2EnterInitializationModeTYPE *)getAdr(&s, h, "fmi2EnterInitializationMode");
	fmu.exitInitializationMode = (fmi2ExitInitializationModeTYPE *)getAdr(&s, h, "fmi2ExitInitializationMode");
	fmu.terminate = (fmi2TerminateTYPE *)getAdr(&s, h, "fmi2Terminate");
	fmu.reset = (fmi2ResetTYPE *)getAdr(&s, h, "fmi2Reset");
	fmu.getReal = (fmi2GetRealTYPE *)getAdr(&s, h, "fmi2GetReal");
	fmu.getInteger = (fmi2GetIntegerTYPE *)getAdr(&s, h, "fmi2GetInteger");
	fmu.getBoolean = (fmi2GetBooleanTYPE *)getAdr(&s, h, "fmi2GetBoolean");
	fmu.getString = (fmi2GetStringTYPE *)getAdr(&s, h, "fmi2GetString");
	fmu.setReal = (fmi2SetRealTYPE *)getAdr(&s, h, "fmi2SetReal");
	fmu.setInteger = (fmi2SetIntegerTYPE *)getAdr(&s, h, "fmi2SetInteger");
	fmu.setBoolean = (fmi2SetBooleanTYPE *)getAdr(&s, h, "fmi2SetBoolean");
	fmu.setString = (fmi2SetStringTYPE *)getAdr(&s, h, "fmi2SetString");
	fmu.getFMUstate = (fmi2GetFMUstateTYPE *)getAdr(&s, h, "fmi2GetFMUstate");
	fmu.setFMUstate = (fmi2SetFMUstateTYPE *)getAdr(&s, h, "fmi2SetFMUstate");
	fmu.freeFMUstate = (fmi2FreeFMUstateTYPE *)getAdr(&s, h, "fmi2FreeFMUstate");
	fmu.serializedFMUstateSize = (fmi2SerializedFMUstateSizeTYPE *)getAdr(&s, h, "fmi2SerializedFMUstateSize");
	fmu.serializeFMUstate = (fmi2SerializeFMUstateTYPE *)getAdr(&s, h, "fmi2SerializeFMUstate");
	fmu.deSerializeFMUstate = (fmi2DeSerializeFMUstateTYPE *)getAdr(&s, h, "fmi2DeSerializeFMUstate");
	fmu.getDirectionalDerivative = (fmi2GetDirectionalDerivativeTYPE *)getAdr(&s, h, "fmi2GetDirectionalDerivative");

	if (type == FMI_MODEL_EXCHANGE) {
		fmu.enterEventMode = (fmi2EnterEventModeTYPE *)getAdr(&s, h, "fmi2EnterEventMode");
		fmu.newDiscreteStates = (fmi2NewDiscreteStatesTYPE *)getAdr(&s, h, "fmi2NewDiscreteStates");
		fmu.enterContinuousTimeMode = (fmi2EnterContinuousTimeModeTYPE *)getAdr(&s, h, "fmi2EnterContinuousTimeMode");
		fmu.completedIntegratorStep = (fmi2CompletedIntegratorStepTYPE *)getAdr(&s, h, "fmi2CompletedIntegratorStep");
		fmu.setTime = (fmi2SetTimeTYPE *)getAdr(&s, h, "fmi2SetTime");
		fmu.setContinuousStates = (fmi2SetContinuousStatesTYPE *)getAdr(&s, h, "fmi2SetContinuousStates");
		fmu.getDerivatives = (fmi2GetDerivativesTYPE *)getAdr(&s, h, "fmi2GetDerivatives");
		fmu.getEventIndicators = (fmi2GetEventIndicatorsTYPE *)getAdr(&s, h, "fmi2GetEventIndicators");
		fmu.getContinuousStates = (fmi2GetContinuousStatesTYPE *)getAdr(&s, h, "fmi2GetContinuousStates");
		fmu.getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *)getAdr(&s, h, "fmi2GetNominalsOfContinuousStates");
	}
	else if (type == FMI_COSIMULATION) {
		fmu.setRealInputDerivatives = (fmi2SetRealInputDerivativesTYPE *)getAdr(&s, h, "fmi2SetRealInputDerivatives");
		fmu.getRealOutputDerivatives = (fmi2GetRealOutputDerivativesTYPE *)getAdr(&s, h, "fmi2GetRealOutputDerivatives");
		fmu.doStep = (fmi2DoStepTYPE *)getAdr(&s, h, "fmi2DoStep");
		fmu.cancelStep = (fmi2CancelStepTYPE *)getAdr(&s, h, "fmi2CancelStep");
		fmu.getStatus = (fmi2GetStatusTYPE *)getAdr(&s, h, "fmi2GetStatus");
		fmu.getRealStatus = (fmi2GetRealStatusTYPE *)getAdr(&s, h, "fmi2GetRealStatus");
		fmu.getIntegerStatus = (fmi2GetIntegerStatusTYPE *)getAdr(&s, h, "fmi2GetIntegerStatus");
		fmu.getBooleanStatus = (fmi2GetBooleanStatusTYPE *)getAdr(&s, h, "fmi2GetBooleanStatus");
		fmu.getStringStatus = (fmi2GetStringStatusTYPE *)getAdr(&s, h, "fmi2GetStringStatus");
	}

	if (fmu.getVersion == NULL && fmu.instantiate == NULL) {
		//printf("warning: Functions from FMI 2.0 could not be found in %s\n", dllPath);
		//printf("warning: Simulator will look for FMI 2.0 RC1 functions names...\n");
		s = true;
		fmu.getTypesPlatform = (fmi2GetTypesPlatformTYPE *)getAdr(&s, h, "fmiGetTypesPlatform");
		fmu.getVersion = (fmi2GetVersionTYPE *)getAdr(&s, h, "fmiGetVersion");
		fmu.setDebugLogging = (fmi2SetDebugLoggingTYPE *)getAdr(&s, h, "fmiSetDebugLogging");
		fmu.instantiate = (fmi2InstantiateTYPE *)getAdr(&s, h, "fmiInstantiate");
		fmu.freeInstance = (fmi2FreeInstanceTYPE *)getAdr(&s, h, "fmiFreeInstance");
		fmu.setupExperiment = (fmi2SetupExperimentTYPE *)getAdr(&s, h, "fmiSetupExperiment");
		fmu.enterInitializationMode = (fmi2EnterInitializationModeTYPE *)getAdr(&s, h, "fmiEnterInitializationMode");
		fmu.exitInitializationMode = (fmi2ExitInitializationModeTYPE *)getAdr(&s, h, "fmiExitInitializationMode");
		fmu.terminate = (fmi2TerminateTYPE *)getAdr(&s, h, "fmiTerminate");
		fmu.reset = (fmi2ResetTYPE *)getAdr(&s, h, "fmiReset");
		fmu.getReal = (fmi2GetRealTYPE *)getAdr(&s, h, "fmiGetReal");
		fmu.getInteger = (fmi2GetIntegerTYPE *)getAdr(&s, h, "fmiGetInteger");
		fmu.getBoolean = (fmi2GetBooleanTYPE *)getAdr(&s, h, "fmiGetBoolean");
		fmu.getString = (fmi2GetStringTYPE *)getAdr(&s, h, "fmiGetString");
		fmu.setReal = (fmi2SetRealTYPE *)getAdr(&s, h, "fmiSetReal");
		fmu.setInteger = (fmi2SetIntegerTYPE *)getAdr(&s, h, "fmiSetInteger");
		fmu.setBoolean = (fmi2SetBooleanTYPE *)getAdr(&s, h, "fmiSetBoolean");
		fmu.setString = (fmi2SetStringTYPE *)getAdr(&s, h, "fmiSetString");
		fmu.getFMUstate = (fmi2GetFMUstateTYPE *)getAdr(&s, h, "fmiGetFMUstate");
		fmu.setFMUstate = (fmi2SetFMUstateTYPE *)getAdr(&s, h, "fmiSetFMUstate");
		fmu.freeFMUstate = (fmi2FreeFMUstateTYPE *)getAdr(&s, h, "fmiFreeFMUstate");
		fmu.serializedFMUstateSize = (fmi2SerializedFMUstateSizeTYPE *)getAdr(&s, h, "fmiSerializedFMUstateSize");
		fmu.serializeFMUstate = (fmi2SerializeFMUstateTYPE *)getAdr(&s, h, "fmiSerializeFMUstate");
		fmu.deSerializeFMUstate = (fmi2DeSerializeFMUstateTYPE *)getAdr(&s, h, "fmiDeSerializeFMUstate");
		fmu.getDirectionalDerivative = (fmi2GetDirectionalDerivativeTYPE *)getAdr(&s, h, "fmiGetDirectionalDerivative");
		if (type == FMI_MODEL_EXCHANGE) {
			fmu.enterEventMode = (fmi2EnterEventModeTYPE *)getAdr(&s, h, "fmiEnterEventMode");
			fmu.newDiscreteStates = (fmi2NewDiscreteStatesTYPE *)getAdr(&s, h, "fmiNewDiscreteStates");
			fmu.enterContinuousTimeMode = (fmi2EnterContinuousTimeModeTYPE *)getAdr(&s, h, "fmiEnterContinuousTimeMode");
			fmu.completedIntegratorStep = (fmi2CompletedIntegratorStepTYPE *)getAdr(&s, h, "fmiCompletedIntegratorStep");
			fmu.setTime = (fmi2SetTimeTYPE *)getAdr(&s, h, "fmiSetTime");
			fmu.setContinuousStates = (fmi2SetContinuousStatesTYPE *)getAdr(&s, h, "fmiSetContinuousStates");
			fmu.getDerivatives = (fmi2GetDerivativesTYPE *)getAdr(&s, h, "fmiGetDerivatives");
			fmu.getEventIndicators = (fmi2GetEventIndicatorsTYPE *)getAdr(&s, h, "fmiGetEventIndicators");
			fmu.getContinuousStates = (fmi2GetContinuousStatesTYPE *)getAdr(&s, h, "fmiGetContinuousStates");
			fmu.getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *)getAdr(&s, h, "fmiGetNominalsOfContinuousStates");
		}
		else if (type == FMI_COSIMULATION) {
			fmu.setRealInputDerivatives = (fmi2SetRealInputDerivativesTYPE *)getAdr(&s, h, "fmiSetRealInputDerivatives");
			fmu.getRealOutputDerivatives = (fmi2GetRealOutputDerivativesTYPE *)getAdr(&s, h, "fmiGetRealOutputDerivatives");
			fmu.doStep = (fmi2DoStepTYPE *)getAdr(&s, h, "fmiDoStep");
			fmu.cancelStep = (fmi2CancelStepTYPE *)getAdr(&s, h, "fmiCancelStep");
			fmu.getStatus = (fmi2GetStatusTYPE *)getAdr(&s, h, "fmiGetStatus");
			fmu.getRealStatus = (fmi2GetRealStatusTYPE *)getAdr(&s, h, "fmiGetRealStatus");
			fmu.getIntegerStatus = (fmi2GetIntegerStatusTYPE *)getAdr(&s, h, "fmiGetIntegerStatus");
			fmu.getBooleanStatus = (fmi2GetBooleanStatusTYPE *)getAdr(&s, h, "fmiGetBooleanStatus");
			fmu.getStringStatus = (fmi2GetStringStatusTYPE *)getAdr(&s, h, "fmiGetStringStatus");
		}
	}
	return s;
}

void* FMISupport::getAdr(bool *success, HMODULE dllHandle, const char *functionName) {
	void* fp = GetProcAddress(dllHandle, functionName);
	if (!fp) {
		*success = false;
	}
	return fp;
}

void FMISupport::unLoad() {
	FreeLibrary(fmu.dllHandle);
	freeModelDescription(fmu.modelDescription);
	ostringstream ss;
	string str;
	ss << "rmdir /S /Q " << currentDir << OUT_PATH;
	str = ss.str();
	system(str.c_str());
}

InterfaceResponse<bool>* FMISupport::simulateByCs(
	double tStart,
	double tEnd,
	double h,
	fmi2Boolean loggingOn,
	char separator,
	int nCategories,
	char **categories) {

	string resultMsg = "hello";
	ModelDescription* md = fmu.modelDescription;
	//获取信息
	const char* guid = getAttributeValue((Element*)md, att_guid);
	const char *instanceName = getAttributeValue((Element*)getCoSimulation(md), att_modelIdentifier);

	ostringstream ss;
	string str;

	ss << currentDir << OUT_PATH << "resources\\";
	str = ss.str();

	//回调
	fmi2CallbackFunctions callbacks = { fmuLogger, calloc, free, NULL, &fmu };
	

	//是否有可视化组件
	fmi2Boolean visible = fmi2False;

	fmi2Component c = fmu.instantiate(instanceName, fmi2CoSimulation, guid, str.c_str(), &callbacks, visible, loggingOn);

	if (!c) {
		return InterfaceResponse<bool>::createByErrorMessage("could not instantiate model");
	}
	
	if (nCategories > 0) {
		fmi2Status fmi2Flag = fmu.setDebugLogging(c, fmi2True, nCategories, categories);
		if (fmi2Flag > fmi2Warning) {
			return InterfaceResponse<bool>::createByErrorMessage("failed FMI set debug logging");
		}
	}

	Element *defaultExp = getDefaultExperiment(md);
	fmi2Boolean toleranceDefined = fmi2False;
	fmi2Real tolerance = 0;

	ValueStatus vs;
	if (defaultExp) {
		tolerance = getAttributeDouble(defaultExp, att_tolerance, &vs);
		if (vs == valueDefined) {
			toleranceDefined = fmi2True;
		}
	}

	fmi2Status fmi2Flag = fmu.setupExperiment(c, toleranceDefined, tolerance, tStart, fmi2True, tEnd);
	if (fmi2Flag > fmi2Warning) {
		return InterfaceResponse<bool>::createByErrorMessage("failed FMI setup experiment");
	}

	fmi2Flag = fmu.enterInitializationMode(c);
	if (fmi2Flag > fmi2Warning) {
		return InterfaceResponse<bool>::createByErrorMessage("failed FMI enter initialization mode");
	}

	fmi2Flag = fmu.exitInitializationMode(c);
	if (fmi2Flag > fmi2Warning) {
		return InterfaceResponse<bool>::createByErrorMessage("failed FMI exit initialization mode");
	}

	//TODO


	int nSteps = 0;
	double hh = h;
	double time = tStart;
	while (time < tEnd) {
		//最后不足一步按实际来
		if (h > tEnd - time) {
			hh = tEnd - time;
		}
		fmi2Flag = fmu.doStep(c, time, hh, fmi2True);
		if (fmi2Flag == fmi2Discard) {
			fmi2Boolean b;
			if (fmi2OK != fmu.getBooleanStatus(c, fmi2Terminated, &b)) {
				return InterfaceResponse<bool>::createByErrorMessage(
					"could not complete simulation of the model. getBooleanStatus return other than fmi2OK");
			}
			if (b == fmi2True) {
				return InterfaceResponse<bool>::createByErrorMessage("the model requested to end the simulation");
			}
			return InterfaceResponse<bool>::createByErrorMessage("could not complete simulation of the model 1");
		}
		if (fmi2Flag != fmi2OK) {
			return InterfaceResponse<bool>::createByErrorMessage("could not complete simulation of the model 2");
		}
		time += hh;
		//outputRow(fmu, c, time, file, separator, fmi2False);
		//计步
		nSteps++;
	}

	fmu.terminate(c);
	fmu.freeInstance(c);
	

	return InterfaceResponse<bool>::createBySuccessMessage(resultMsg);
}

#define MAX_MSG_SIZE 1000
void fmuLogger(
	void *componentEnvironment,
	fmi2String instanceName,
	fmi2Status status,
	fmi2String category,
	fmi2String message,
	...) {

	char msg[MAX_MSG_SIZE];
	char* copy;
	va_list argp;

	// replace C format strings
	va_start(argp, message);
	vsprintf(msg, message, argp);
	va_end(argp);

	// replace e.g. ## and #r12#
	copy = strdup(msg);
	replaceRefsInMessage(copy, msg, MAX_MSG_SIZE, (FMU*)componentEnvironment);
	free(copy);

	// print the final message
	if (!instanceName) instanceName = "?";
	if (!category) category = "?";
	printf("%s %s (%s): %s\n", fmi2StatusToString(status), instanceName, category, msg);
}
// replace e.g. #r1365# by variable name and ## by # in message
// copies the result to buffer
void replaceRefsInMessage(const char* msg, char* buffer, int nBuffer, FMU* fmu) {
	int i = 0; // position in msg
	int k = 0; // position in buffer
	int n;
	char c = msg[i];
	while (c != '\0' && k < nBuffer) {
		if (c != '#') {
			buffer[k++] = c;
			i++;
			c = msg[i];
		}
		else if (strlen(msg + i + 1) >= 3
			&& (strncmp(msg + i + 1, "IND", 3) == 0 || strncmp(msg + i + 1, "INF", 3) == 0)) {
			// 1.#IND, 1.#INF
			buffer[k++] = c;
			i++;
			c = msg[i];
		}
		else {
			char* end = (char*)strchr(msg + i + 1, '#');
			if (!end) {
				printf("unmatched '#' in '%s'\n", msg);
				buffer[k++] = '#';
				break;
			}
			n = end - (msg + i);
			if (n == 1) {
				// ## detected, output #
				buffer[k++] = '#';
				i += 2;
				c = msg[i];

			}
			else {
				char type = msg[i + 1]; // one of ribs
				fmi2ValueReference vr;
				int nvr = sscanf(msg + i + 2, "%u", &vr);
				if (nvr == 1) {
					// vr of type detected, e.g. #r12#
					ScalarVariable* sv = getSV(fmu, type, vr);
					const char* name = sv ? getAttributeValue((Element *)sv, att_name) : "?";
					sprintf(buffer + k, "%s", name);
					k += strlen(name);
					i += (n + 1);
					c = msg[i];

				}
				else {
					// could not parse the number
					printf("illegal value reference at position %d in '%s'\n", i + 2, msg);
					buffer[k++] = '#';
					break;
				}
			}
		}
	} // while
	buffer[k] = '\0';
}
// search a fmu for the given variable, matching the type specified.
// return NULL if not found
ScalarVariable* getSV(FMU* fmu, char type, fmi2ValueReference vr) {
	int i;
	int n = getScalarVariableSize(fmu->modelDescription);
	Elm tp;

	switch (type) {
	case 'r': tp = elm_Real;    break;
	case 'i': tp = elm_Integer; break;
	case 'b': tp = elm_Boolean; break;
	case 's': tp = elm_String;  break;
	default: tp = elm_BAD_DEFINED;
	}
	for (i = 0; i < n; i++) {
		ScalarVariable* sv = getScalarVariable(fmu->modelDescription, i);
		if (vr == getValueReference(sv) && tp == getElementType(getTypeSpec(sv))) {
			return sv;
		}
	}
	return NULL;
}
const char* fmi2StatusToString(fmi2Status status) {
	switch (status) {
	case fmi2OK:      return "ok";
	case fmi2Warning: return "warning";
	case fmi2Discard: return "discard";
	case fmi2Error:   return "error";
	case fmi2Fatal:   return "fatal";
	case fmi2Pending:
	{
		//if (type == FMI_COSIMULATION) {
			return "fmi2Pending";
		//}
	}
	default:         return "?";
	}
}