
#include "ControlCode.h"
#include "StateMachineCode.h"

QString ControlCode::TYPE_PAUSE = "PAUSE";
QString ControlCode::TYPE_CONTINUE = "CONTINUE";
QString ControlCode::TYPE_END = "END";

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