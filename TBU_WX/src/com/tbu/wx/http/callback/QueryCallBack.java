package com.tbu.wx.http.callback;

import com.tbu.wx.http.data.WxUserInfo;

public interface QueryCallBack {
	void queryCallBackMsg(WxUserInfo info);
}
