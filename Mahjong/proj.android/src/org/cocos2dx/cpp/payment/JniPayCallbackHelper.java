package org.cocos2dx.cpp.payment;

public class JniPayCallbackHelper {
	//0表示时间失败,1表示成功，2表示事件关闭
	public static native void eventCallBack(int eventId, int result);
	public static native void loginThirdPlatform(String openid);
	public static native void loadImageByURL(String url,String sex);
}
