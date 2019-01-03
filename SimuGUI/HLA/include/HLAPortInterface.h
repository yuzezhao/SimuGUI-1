// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HLAPORTINTERFACE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HLAPORTINTERFACE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

/*
* Interface层
* @date : 2018/09/22
* @author : jihang
*/

#include "ObjectClassSet.h"
#include "InterfaceResponse.h"

using namespace std;

#ifdef HLAPORTINTERFACE_EXPORTS
#define HLAPORTINTERFACE_API __declspec(dllexport)
#else
#define HLAPORTINTERFACE_API __declspec(dllimport)
#endif

#define READY_TO_RUN "ReadyToRun"

// 此类是从 HLAPortInterface.dll 导出的
class HLAPORTINTERFACE_API CHLAPortInterface {
public:
	//构造/析构
public:
	CHLAPortInterface();
	virtual ~CHLAPortInterface() {};

public:
	//暂停状态位
	bool isPause;
	//结束状态位
	bool isEnd;
	//联邦文件
	string m_fedFile;
	//联邦名
	string m_federationName;
	//联邦成员名
	string m_federateName;
	//联邦成员ID
	long m_federateId;

	//接口方法
public:
	//创建联邦
	InterfaceResponse<bool>* createFederation();
	//加入联邦，返回联邦成员ID，失败返回-1，默认加入fed文件中定义的联邦名称
	InterfaceResponse<long>* joinFederation();
	//退出联邦
	InterfaceResponse<bool>* resignFederation();
	//撤销联邦，默认销毁fed文件中定义的联邦名称
	InterfaceResponse<bool>* destroyFederation();
	//初始化句柄，目前仅限对象类，仅限一条
	InterfaceResponse<bool>* initOneHandle(ObjectClassSet&);
	//注册联邦同步点
	InterfaceResponse<bool>* registerSynchronization(string label);
	//运行到同步点
	InterfaceResponse<bool>* synchronizationAchieved(string label);
	//设置时间策略
	InterfaceResponse<bool>* enableTimePolicy(double lookahead);
	//发布对象类，目前仅限对象类，仅限一条
	InterfaceResponse<bool>* publishOne(ObjectClassSet&);
	//订阅对象类，目前仅限对象类，仅限一条
	InterfaceResponse<bool>* subscribeOne(ObjectClassSet&);
	//注册对象类
	InterfaceResponse<long>* registerObject(string className);
	//发送对象类，目前仅限对象类
	InterfaceResponse<bool>* sendObject(RTI::ObjectHandle, RTI::AttributeHandleValuePairSet*);
	//时间步进
	InterfaceResponse<bool>* advanceTime(double timestep);
	//删除对象类，目前仅限对象类
	InterfaceResponse<bool>* deleteOne(RTI::ObjectHandle);
	//通过类句柄定位对象类
	InterfaceResponse<long>* getObjectClass(RTI::ObjectHandle objectHandle);
	//获取当前时间
	InterfaceResponse<double>* getCurrentTime();

	//=======================以下为回调==========================
	//同步成功
	virtual void syncSuccess(const char *label) = 0;
	//同步失败
	virtual void syncFailure(const char *label) = 0;
	//声明同步
	virtual void announceSync(
		const char *label, const char *tag) = 0;
	//完成同步
	virtual void syncComplete(const char *label) = 0;
	//发现对象实例
	virtual void discover(RTI::ObjectHandle theObject,
		RTI::ObjectClassHandle theObjectClass,
		const char * theObjectName) = 0;
	//接收对象类,目前仅限对象类
	virtual void processData(RTI::ObjectHandle,
		const RTI::AttributeHandleValuePairSet&, const char*) = 0;
	//删除对象实例
	virtual void remove(RTI::ObjectHandle theObject, const char *theTag) = 0;
};
