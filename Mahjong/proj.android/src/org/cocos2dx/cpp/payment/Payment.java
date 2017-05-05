package org.cocos2dx.cpp.payment;

import java.text.SimpleDateFormat;
import java.util.Date;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.callback.WechatLoginCallBack;
import com.tbu.wx.http.callback.WxPayCallBack;
import com.tbu.wx.http.data.WxUserInfo;
import com.tbu.wx.wechat.TbuWxUtil;

import android.app.Activity;
import android.os.Environment;

public class Payment {

	public static String eventId = null;// 计费点编号
	private static String weChatState = null;// 微信用于保持请求和回调的状态，授权请求后原样带回给第三方
	private static Activity activity;
	private static String pxOrderId = null;// 支付订单
	private static final String POXIAOSIGN = "poxiaosign";

	public static void init(Activity activity) {
		Payment.activity = activity;
		TbuWxUtil.getInstance().initOnFirstActivity(Payment.activity);
	}

	/**
	 * 微信支付下单
	 * 
	 * @param poxiaoId
	 * @param payPoint
	 */
	public static void requestEvent(final String poxiaoId, final String payPoint) {
		Debug.i("Payment start requestEvent ...");
		TbuWxUtil.getInstance().Pay(poxiaoId, payPoint, new WxPayCallBack() {
			@Override
			public void wxPayCallback(String orderId) {
				pxOrderId = orderId;
				eventId = payPoint;
				Debug.e("破晓支付的订单编号:" + pxOrderId);
			}
		});
	}

	/**
	 * 微信支付结果查询
	 */
	public static void queryPayResult() {
		Debug.i("Payment start queryPayResult ...");
		if (null != pxOrderId) {
			TbuWxUtil.getInstance().queryOrder(pxOrderId, new QueryCallBack() {

				@Override
				public void queryCallBackMsg(WxUserInfo info) {
					if (info.isResult()) {
						JniPayCallbackHelper.eventCallBack(Integer.valueOf(Payment.eventId), 1);
					} else {
						JniPayCallbackHelper.eventCallBack(Integer.valueOf(Payment.eventId), 0);
					}
				}
			});
		}
	}

	/**
	 * 微信分享
	 * 
	 * @param webpageUrl
	 * @param title
	 * @param description
	 * @param friends
	 */
	public static void shareToWeChat(String webpageUrl, String title, String description, boolean friends) {
		TbuWxUtil.getInstance().shareWebPage(webpageUrl, title, description, null, friends);
	}

	/**
	 * 图片分享
	 * 
	 * @param imagePath
	 * @param friends
	 */
	public static void shareImageToWeChat(String imagePath, boolean friends) {
		Debug.e("shareImageToWeChat 分享图片给微信好友");
		TbuWxUtil.getInstance().shareImage(imagePath, friends);
	}

	/**
	 * 发起微信登录
	 */
	public static void weChatLogin() {
		Debug.i("微信登录游戏 weChatLogin...");
		TbuWxUtil.getInstance().getWechatCode(getWeChatState(), new QueryCallBack() {
			@Override
			public void queryCallBackMsg(WxUserInfo info) {
				if (null != info&&!info.isResult()) {
					Debug.i("微信登录游戏...");
					JniPayCallbackHelper.loginThirdPlatform(info.getOpenId(),info.getUnionid(),
							info.getHeadImage(), info.getSex(), info.getNickName(), DeviceInfo.getProduct(),
							DeviceInfo.getModle(), DeviceInfo.getImsi(), DeviceInfo.getImei(), AppInfo.getVersion());
				}
			}

		});

	}

	public static void clearWechatOpenId() {
		TbuWxUtil.getInstance().clearOpenId();
	}

	/**
	 * 获取微信的token
	 * 
	 * @param code
	 * @param tcallback
	 */
	public static void getWechatToken(String code, final WechatLoginCallBack tcallback) {
		TbuWxUtil.getInstance().getWechatToken(code, new WechatLoginCallBack() {

			@Override
			public void callBack(WxUserInfo info) {
				tcallback.callBack(info);

			}
		});
	}

	/**
	 * 获取sd卡路径
	 * 
	 * @return
	 */
	private static final String SDCARD_ROOT = Environment.getExternalStorageDirectory().getAbsolutePath();

	public static String getSdCardDir() {
		return SDCARD_ROOT;
	}

	// 获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}

	public static String getWeChatState() {
		if (null == weChatState) {
			weChatState = POXIAOSIGN + getDateFormat();
		}
		// Debug.e("weChatState = "+weChatState);
		return weChatState;
	}

}
