package org.cocos2dx.cpp.network;

import android.util.Log;

public class AndroidSocketJni {
	// 连接服务器
	public static void connectSocket(String ip, String port) {
		Log.e("AndroidSocket", "Socket连接服务器");
		PxSocketClient.getInstance().connect(ip, port);
	}

	public static void sendDataSever(String msg) {
		Log.e("AndroidSocket", "向服务端发送数据:" + msg);
		PxSocketClient.getInstance().sendDataSever(msg);
	}
}
