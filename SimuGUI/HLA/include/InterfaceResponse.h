#pragma once

/*
* 接口统一回复类
* @date : 2018/10/16
* @author : jihang
*/

#include <iostream>

using namespace std;

template <typename T>
class InterfaceResponse {

private:
	bool isSucess;
	string message;
	T data;

private:
	//Interface是封装的，所以用户不知道是否回复了message，取消无message接口
	//InterfaceResponse(bool isSuc) {
	//	isSucess = isSuc;
	//}
	InterfaceResponse(bool isSuc, string msg) {
		isSucess = isSuc;
		message = msg;
	}
	//Interface是封装的，所以用户不知道是否回复了message，取消无message接口
	//InterfaceResponse(bool isSuc, T* t) {
	//	isSucess = isSuc;
	//	data = t;
	//}
	InterfaceResponse(bool isSuc, string msg, T t) {
		isSucess = isSuc;
		message = msg;
		data = t;
	}

public:
	bool isSuccessful() {
		return isSucess;
	}
	string getMessage() {
		return message;
	}
	T getData() {
		return data;
	}

public:
	//static InterfaceResponse* createBySuccess() {
	//	return new InterfaceResponse(true);
	//}
	static InterfaceResponse* createBySuccessMessage(string msg) {
		return new InterfaceResponse(true, msg);
	}
	//static InterfaceResponse* createBySuccessData(T t) {
	//	return new InterfaceResponse(true, t);
	//}
	static InterfaceResponse* createBySuccessMessageAndData(string msg, T t) {
		return new InterfaceResponse(true, msg, t);
	}
	//static InterfaceResponse* createByError() {
	//	return new InterfaceResponse(true);
	//}
	static InterfaceResponse* createByErrorMessage(string msg) {
		return new InterfaceResponse(false, msg);
	}
};