
#include <sstream>
#include <stdio.h>
#include <direct.h>
#include <Windows.h>

#include "FMISupport.h"

#define UNZIP_CMD "./FMIpackage/7z/7z x -aoa -o "
// -x   Extracts files from an archive with their full paths in the current dir, or in an output dir if specified
// -aoa Overwrite All existing files without prompt
// -o   Specifies a destination directory where files are to be extracted

#define OUT_PATH "\"FMIpackage\\tmp\" "

#define SEVEN_ZIP_NO_ERROR 0
#define SEVEN_ZIP_WARNING 1
#define SEVEN_ZIP_ERROR 2
#define SEVEN_ZIP_COMMAND_LINE_ERROR 7
#define SEVEN_ZIP_OUT_OF_MEMORY 8
#define SEVEN_ZIP_STOPPED_BY_USER 255

InterfaceResponse<bool>* FMISupport::loadFMU(const char *filePath) {

	LPWSTR Fname = { 0 };

	GetModuleFileName(NULL, Fname, sizeof(Fname));

	ostringstream ss;
	ss << UNZIP_CMD << Fname << OUT_PATH << "\"" << filePath << "\" > NUL";
	string str = ss.str();

	return InterfaceResponse<bool>::createByErrorMessage(str.c_str());

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
	return InterfaceResponse<bool>::createBySuccessMessage("yeah");
}