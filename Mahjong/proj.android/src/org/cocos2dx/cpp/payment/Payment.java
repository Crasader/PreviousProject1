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

	public static void requestEvent(int eventId) {
		// 通过josn获取事件
		final TbuEvent event = TbuAndroidTools.getTbuEventById(activity, eventId);
		if (null != event) {
			if (event.getEventState()) {
				// 匹配相应的计费点
				final PayPoint payPoint = TbuAndroidTools.getPayPointById(activity, event.getPayId());

				TbuWxPay.getInstance().Pay(getDateFormat(), AppInfo.getTbuId(), String.valueOf(payPoint.getType()),
						payPoint.getName(), String.valueOf(payPoint.getMoney()));
				JniPayCallbackHelper.eventCallBack(eventId, 1, null, null);
			} else {
				Debug.i("Payment->requestEvent:事件点处于关闭状态");
			}
		} else {
			Debug.i("Payment->requestEvent:无法找到事件点:"+eventId);
		}
	}
	
	//获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}
}
