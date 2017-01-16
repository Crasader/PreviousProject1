package org.cocos2dx.cpp.network;

public class JniSocketCallback {
	public static native void dataRecieve(String data);
	public static native void onDisconnected();
}
