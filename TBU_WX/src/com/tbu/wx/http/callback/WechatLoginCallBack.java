package com.tbu.wx.http.callback;

import com.tbu.wx.http.data.WxUserInfo;

public interface WechatLoginCallBack {
	void callBack(WxUserInfo info); 
}
