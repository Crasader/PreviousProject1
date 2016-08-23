package org.cocos2dx.cpp.payment;

import com.tbu.wx.pay.TbuWxPay;

import android.app.Activity;
import android.util.Log;

public class Payment {
	
	private static Activity activity;

	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxPay.getInstance().initOnFirstActivity(activity);
	}

	public static void pay(int payId) {
		Log.e("Mahjong","pay to wechat");
		TbuWxPay.getInstance().Pay("20160822", "201503", "1", "abc", "100");
	}	
}
