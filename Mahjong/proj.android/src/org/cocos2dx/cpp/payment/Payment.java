package org.cocos2dx.cpp.payment;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.util.event.TbuEvent;
import com.tbu.androidtools.util.paypoint.PayPoint;
import com.tbu.wx.pay.TbuWxPay;
import android.app.Activity;

public class Payment {

	private static Activity activity;

	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxPay.getInstance().initOnFirstActivity(activity);
	}

	public static void requestEvent(String poxiaoId,String payPoint) {
		Debug.e("requestEvent start wx pay ...");
		TbuWxPay.getInstance().Pay(poxiaoId,payPoint);
	}
	
	//获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}
}
