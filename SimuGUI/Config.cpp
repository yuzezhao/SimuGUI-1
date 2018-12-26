
//#include "ControlCode.h"
//#include "CallbackCode.h"
#include "StateMachineCode.h"
/*
QString ControlCode::TYPE_PAUSE = "PAUSE";
QString ControlCode::TYPE_CONTINUE = "CONTINUE";
QString ControlCode::TYPE_END = "END";

int ControlCode::CODE_PAUSE = 5001;
int ControlCode::CODE_CONTINUE = 5002;
int ControlCode::CODE_END = 5003;

int ControlCode::CODE_TIME = 5004;
int ControlCode::CODE_PRINT = 5005;

int CallbackCode::CODE_SyncSuccess = 6001;
int CallbackCode::CODE_SyncFailure = 6002;
int CallbackCode::CODE_AnnounceSync = 6003;
int CallbackCode::CODE_SyncComplete = 6004;
int CallbackCode::CODE_Discover = 6005;
int CallbackCode::CODE_Remove = 6006;
int CallbackCode::CODE_ProcessData = 6007;
*/
int StateMachineCode::CODE_UNSTART = 7001;
int StateMachineCode::CODE_JOINED = 7002;
int StateMachineCode::CODE_INITIALED = 7003;
int StateMachineCode::CODE_REGISPOINT = 7004;
int StateMachineCode::CODE_SYNCHED = 7005;
int StateMachineCode::CODE_TIMEENABLED = 7006;
int StateMachineCode::CODE_PUBANDSUB = 7007;
int StateMachineCode::CODE_REGISTERED = 7008;
int StateMachineCode::CODE_RUNNING = 7009;
int StateMachineCode::CODE_END = 7010;