package org.cocos2dx.cpp.payment;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.tbu.androidtools.Debug;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.callback.WxPayCallBack;
import com.tbu.wx.pay.TbuWxUtil;

import android.app.Activity;

public class Payment {

	public static String eventId = null;//计费点编号
	private static Activity activity;
    private static String pxOrderId = null;//支付订单
    
	
	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxUtil.getInstance().initOnFirstActivity(Payment.activity);
	}

	/**
	 * 微信支付下单
	 * @param poxiaoId
	 * @param payPoint
	 */
	public static void requestEvent(final String poxiaoId,final String payPoint) {
		Debug.i("Payment start requestEvent ...");
		TbuWxUtil.getInstance().Pay(poxiaoId,payPoint,new WxPayCallBack() {		
			@Override
			public void wxPayCallback(String orderId) {
				pxOrderId = orderId;
				eventId = payPoint;
				Debug.e("破晓支付的订单编号:"+pxOrderId);
			}
		});
	}
	
	/**
	 * 微信支付结果查询
	 */
	public static void queryPayResult() {
		Debug.i("Payment start queryPayResult ...");
		if(null != pxOrderId){
			TbuWxUtil.getInstance().queryOrder(pxOrderId,new QueryCallBack() {	
				@Override
				public void queryCallback(boolean result) {
					if(result){
						JniPayCallbackHelper.eventCallBack(Integer.valueOf(Payment.eventId) , 1);
					}else{
						JniPayCallbackHelper.eventCallBack(Integer.valueOf(Payment.eventId) , 0);
					}
				}
			});
		}
	}
	
	public static void shareToWeChat(String webpageUrl,String title,String description,boolean friends){
		TbuWxUtil.getInstance().shareWebPage(webpageUrl, title, description, friends);
	}
	
	//获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}
}
