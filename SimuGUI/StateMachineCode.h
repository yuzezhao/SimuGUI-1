#pragma once

/*
* ÊÊÅäÆ÷ÀàµÄ×´Ì¬»ú
* @date : 2018/10/28
* @author : jihang
*/

class StateMachineCode {

private:
	static int CODE_UNSTART;
	static int CODE_JOINED;
	static int CODE_INITIALED;
	static int CODE_REGISPOINT;
	static int CODE_SYNCHED;
	static int CODE_TIMEENABLED;
	static int CODE_PUBANDSUB;
	static int CODE_REGISTERED;
	static int CODE_RUNNING;
	static int CODE_END;

public:
	static int getUnstartCode() {
		return CODE_UNSTART;
	}
	static int getJoinedCode() {
		return CODE_JOINED;
	}
	static int getInitialedCode() {
		return CODE_INITIALED;
	}
	static int getRegisPointCode() {
		return CODE_REGISPOINT;
	}
	static int getSynchedCode() {
		return CODE_SYNCHED;
	}
	static int getTimeEnabledCode() {
		return CODE_TIMEENABLED;
	}
	static int getPubAndSubCode() {
		return CODE_PUBANDSUB;
	}
	static int getRegisteredCode() {
		return CODE_REGISTERED;
	}
	static int getRunningCode() {
		return CODE_RUNNING;
	}
	static int getEndCode() {
		return CODE_END;
	}
};