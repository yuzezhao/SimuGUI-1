#pragma once

/*
* RunControlAdapter层
* @date : 2018/10/13
* @author : jihang
*/

#include <QObject>

#include "HLAPortInterface.h"

class HLAPortAdapter : public QObject, public CHLAPortInterface {

	Q_OBJECT

public:
	//1.对象类定义
	//仿真控制，目前共三组，全部发布
	ObjectClassSet objectPause;
	RTI::ObjectHandle handlePause;

	ObjectClassSet objectContinue;
	RTI::ObjectHandle handleContinue;

	ObjectClassSet objectEnd;
	RTI::ObjectHandle handleEnd;

	//订阅，是否能获得全局所有？
	ObjectClassSet objectA;
	ObjectClassSet objectB;

public:
	//2.构造函数
	explicit HLAPortAdapter(QObject *parent = NULL);
	virtual ~HLAPortAdapter() {};

public:
	void initial();

	void pubAndSub();

	void rigister();

	void simulate();

	void send(QString type);

	void del();

	//=======================以下为回调==========================
	void processData(RTI::ObjectHandle, const RTI::AttributeHandleValuePairSet&, const char*);

	void syncSuccess(const char*);

	void syncFailure(const char*);

	void announceSync(const char*, const char*);

	void syncComplete(const char*);

	void discover(RTI::ObjectHandle, RTI::ObjectClassHandle, const char*);

	void remove(RTI::ObjectHandle, const char*);

signals:
	//发给UI的信号
	void postUIMsg(QString);
	//发给UI的时间
	void postUITime(double);
};