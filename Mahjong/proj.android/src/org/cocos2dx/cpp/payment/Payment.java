package org.cocos2dx.cpp.payment;

import com.tbu.wx.pay.TbuWxPay;

import android.app.Activity;

public class Payment {
	
	private static Activity activity;

	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxPay.getInstance().initOnFirstActivity(activity);
	}

	public static void pay(final String orderId, final String tbuId,
			final String productId, final String productName, final String price) {
		TbuWxPay.getInstance().Pay(orderId, tbuId, productId, productName, price);
	}	
}
