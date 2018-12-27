#pragma once

/*
* 等做到暂停、继续功能再加说明
* @date : 2018/10/23
* @author : jihang
*/

#include <QString>

class ControlCode {

private:
	//这个地方对应了对象类的类名
	static QString TYPE_PAUSE;
	static QString TYPE_CONTINUE;
	static QString TYPE_END;

public:
	static QString getPauseType() {
		return TYPE_PAUSE;
	}
	static QString getContinueType() {
		return TYPE_CONTINUE;
	}
	static QString getEndType() {
		return TYPE_END;
	}
};