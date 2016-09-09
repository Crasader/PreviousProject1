package org.cocos2dx.cpp.payment;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.tbu.androidtools.Debug;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.callback.WxPayCallBack;
import com.tbu.wx.pay.TbuWxPay;

import android.app.Activity;

public class Payment {

	private static Activity activity;
    private static String pxOrderId = null;//支付订单
	
	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxPay.getInstance().initOnFirstActivity(Payment.activity);
	}

	/**
	 * 微信支付下单
	 * @param poxiaoId
	 * @param payPoint
	 */
	public static void requestEvent(String poxiaoId,String payPoint) {
		Debug.e("Payment start requestEvent ...");
		TbuWxPay.getInstance().Pay(poxiaoId,payPoint,new WxPayCallBack() {		
			@Override
			public void wxPayCallback(String orderId) {
				pxOrderId = orderId;
				Debug.e("破晓支付的订单编号:"+pxOrderId);
			}
		});
	}
	
	/**
	 * 微信支付结果查询
	 */
	public static boolean queryPayResult() {
		Debug.e("Payment start queryPayResult ...");
		if(null != pxOrderId){
			TbuWxPay.getInstance().queryOrder(pxOrderId,new QueryCallBack() {	
				@Override
				public boolean queryCallback(boolean result) {
					return result;
				}
			});
		}
		return false;
	}
	//获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}
}
