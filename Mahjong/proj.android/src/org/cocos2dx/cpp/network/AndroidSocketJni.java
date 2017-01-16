package org.cocos2dx.cpp.network;

import android.util.Log;

public class AndroidSocketJni {
	// 连接服务器
	public static void connectSocket(String ip, String port) {
		Log.i("AndroidSocket", "Socket连接服务器");
		PxSocketClient.getInstance().connect(ip, port);
	}

	public static void sendDataSever(String msg) {
		PxSocketClient.getInstance().sendDataSever(msg);
	}
}
