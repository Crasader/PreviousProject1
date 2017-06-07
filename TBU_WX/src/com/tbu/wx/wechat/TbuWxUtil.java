package com.tbu.wx.wechat;

import java.io.File;

import org.json.JSONException;
import org.json.JSONObject;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.wx.http.Addresses;
import com.tbu.wx.http.HttpUtil;
import com.tbu.wx.http.KeyValue;
import com.tbu.wx.http.callback.HttpCallBack;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.callback.WechatLoginCallBack;
import com.tbu.wx.http.callback.WxPayCallBack;
import com.tbu.wx.http.data.WxOrderInfo;
import com.tbu.wx.http.data.WxUserInfo;
import com.tbu.wx.util.Util;
import com.tbu.wx.util.WxAppInfo;
import com.tencent.mm.opensdk.modelmsg.SendAuth;
import com.tencent.mm.opensdk.modelmsg.SendMessageToWX;
import com.tencent.mm.opensdk.modelmsg.WXAppExtendObject;
import com.tencent.mm.opensdk.modelmsg.WXImageObject;
import com.tencent.mm.opensdk.modelmsg.WXMediaMessage;
import com.tencent.mm.opensdk.modelmsg.WXWebpageObject;
import com.tencent.mm.opensdk.modelpay.PayReq;
import com.tencent.mm.opensdk.openapi.IWXAPI;
import com.tencent.mm.opensdk.openapi.WXAPIFactory;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.widget.Toast;

public class TbuWxUtil {

	private static final String SDCARD_ROOT = Environment.getExternalStorageDirectory().getAbsolutePath();
	private static final int THUMB_SIZE = 120; // 150;
	public static final String TOKEN_OUT_TIME = "TOKEN_OUT_TIME";
	private static TbuWxUtil instance;
	private static Activity payActivity;
	private static IWXAPI msgApi;
	private static final String PACKAGEVALUE = "Sign=WXPay";
	// private static final String WECHAT_LOGIN_OPENID = "WECHAT_LOGIN_OPENID";

	private static final String WECHAT_LOGIN_OPENID = "poxiao_game";
	private static final String OPEN_ID_INIT = "OPEN_ID_INIT";
	private static final String UNION_ID_INIT = "UNION_ID_INIT";
	
	public static TbuWxUtil getInstance() {
		if (null == instance) {
			instance = new TbuWxUtil();
		}
		return instance;
	}

	public void initOnFirstActivity(Activity activity) {
		TbuWxUtil.payActivity = activity;
		WxAppInfo.init(activity);
		// 将该app注册到微信
		msgApi = WXAPIFactory.createWXAPI(activity, WxAppInfo.getWxInfo().getAppId(), false);
		msgApi.registerApp(WxAppInfo.getWxInfo().getAppId());
	}

	/**
	 * 下单接口
	 * 
	 * @param orderId
	 * @param tbuId
	 * @param productId
	 * @param productName
	 * @param price
	 */
	public void Pay(final String poxiaoId, final String payPoint, final WxPayCallBack callback) {
		// 启动网络线程
		new Thread(new Runnable() {
			@Override
			public void run() {
				// 向服务器下单
				String content = createOrderInfo(poxiaoId, payPoint);
				HttpUtil.doGet(Addresses.URL_ORDER, content, new HttpCallBack() {
					@Override
					public void callBack(String msg) {

						try {
							JSONObject object = new JSONObject(msg);
							if (object.getInt("result") == 0) {
								WxOrderInfo orderInfo = new WxOrderInfo();
								orderInfo.setPxOrderId(object.getString("px_order_id"));
								orderInfo.setWxPrepayid(object.getString("wx_prepayid"));
								orderInfo.setWxSign(object.getString("wx_sign"));
								orderInfo.setWxTimestamp(object.getString("wx_timestamp"));
								orderInfo.setWxNonceStr(object.getString("wx_nonce_str"));
								orderInfo.setWxpartneri(WxAppInfo.getWxInfo().getPartnerId());
								callback.wxPayCallback(orderInfo.getPxOrderId());

								pay2Wx(orderInfo);
							} else {
								callback.wxPayCallback(null);
							}
						} catch (Exception e) {
							callback.wxPayCallback(null);
						}
					}
				});
			}
		}).start();
	}

	/**
	 * 下单接口
	 * 
	 * @param orderId
	 * @param tbuId
	 * @param productId
	 * @param productName
	 * @param price
	 */
	public void PayForThirdWx(final String poxiaoId, final String payPoint, final WxPayCallBack callback) {
		// 启动网络线程
		new Thread(new Runnable() {
			@Override
			public void run() {
				// 向服务器下单
				String content = createOrderInfo(poxiaoId, payPoint);
				HttpUtil.doGet(Addresses.URL_ORDER_THIRD, content, new HttpCallBack() {
					@Override
					public void callBack(String msg) {

						try {
							JSONObject object = new JSONObject(msg);

							WxOrderInfo orderInfo = new WxOrderInfo();
							orderInfo.setPxOrderId(object.getString("px_order_id"));
							orderInfo.setWxPrepayid(object.getString("wx_prepayid"));
							orderInfo.setWxSign(object.getString("wx_sign"));
							orderInfo.setWxTimestamp(object.getString("wx_timestamp"));
							orderInfo.setWxNonceStr(object.getString("wx_nonce_str"));
							callback.wxPayCallback(orderInfo.getPxOrderId());
							orderInfo.setWxpartneri(object.getString("partnerid"));
							pay2Wx(orderInfo);

						} catch (Exception e) {
							callback.wxPayCallback(null);
						}
					}
				});
			}
		}).start();
	}

	/**
	 * 订单查询
	 * 
	 * @param orderId
	 * @param callBack
	 * @param tbu_id
	 */
	public void queryOrder(final String orderId, final QueryCallBack callBack) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				KeyValue keyValue1 = new KeyValue("order_id", orderId);
				String content = HttpUtil.DoContentJoint(keyValue1);
				HttpUtil.doGet(Addresses.URL_QUERY_ORDER, content, new HttpCallBack() {
					@Override
					public void callBack(String msg) {
						if (null == msg) {

						}
						WxUserInfo info = new WxUserInfo();
						try {
							JSONObject object = new JSONObject(msg);
							if (object.getInt("result") == 1) {

								info.setResult(true);
								callBack.queryCallBackMsg(info);
							} else {
								info.setResult(false);
								callBack.queryCallBackMsg(info);
							}
						} catch (Exception e) {
						}
					}
				});
			}
		}).start();
	}

	/**
	 * 关闭订单
	 * 
	 * @param orderId
	 * @param wxOrderId
	 */
	public void closeWxOrder(final String orderId, final String tbu_id) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				// TODO
			}
		}).start();
	}

	/**
	 * 微信分享
	 * 
	 * @param url
	 * @param title
	 * @param content
	 * @param showfriend
	 */
	public void shareWebPage(String webpageUrl, String title, String description, byte[] thumbData, boolean friends) {
		WXWebpageObject webpage = new WXWebpageObject();
		webpage.webpageUrl = webpageUrl;
		WXMediaMessage msg = new WXMediaMessage(webpage);
		msg.title = title;
		msg.description = description;
		msg.thumbData = thumbData;
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		req.transaction = buildTransaction("webpage");
		req.message = msg;
		req.scene = friends ? SendMessageToWX.Req.WXSceneTimeline : SendMessageToWX.Req.WXSceneSession;

		msgApi.sendReq(req);
	}

	/**
	 * android 目前无法使用
	 * 
	 * @param title
	 * @param description
	 * @param thumbData
	 * @param friends
	 */
	public void shareAppData(String title, String description, byte[] thumbData, boolean friends) {
		final WXAppExtendObject appdata = new WXAppExtendObject();
		appdata.extInfo = "this is ext info";
		final WXMediaMessage msg = new WXMediaMessage();
		msg.title = "this is title";
		msg.description = "this is description";
		msg.mediaObject = appdata;

		SendMessageToWX.Req req = new SendMessageToWX.Req();
		req.transaction = buildTransaction("appdata");
		req.message = msg;
		req.scene = friends ? SendMessageToWX.Req.WXSceneTimeline : SendMessageToWX.Req.WXSceneSession;
		msgApi.sendReq(req);
	}

	/**
	 * 图片分享
	 * 
	 * @param image
	 * @param friends
	 */
	public void shareImage(String image, boolean friends) {
		final String path = image;
		File file = new File(path);
		if (!file.exists()) {
			TbuWxUtil.payActivity.runOnUiThread(new Runnable() {
				public void run() {
					Toast.makeText(TbuWxUtil.payActivity, "share image path = " + path + " not exist",
							Toast.LENGTH_LONG).show();
				}
			});
			return;
		}

		
		WXImageObject imgObj = new WXImageObject();
		imgObj.setImagePath(path);
//		imgObj.imageData  =  Util.bmpToByteArray(thumbBmp, true);

		WXMediaMessage msg = new WXMediaMessage();
		msg.mediaObject = imgObj;

		Bitmap bmp = BitmapFactory.decodeFile(path);
		Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, THUMB_SIZE, THUMB_SIZE, true);
		// bmp.compress(format, quality, stream)
		bmp.recycle();
	
		msg.thumbData = Util.bmpToByteArray(thumbBmp, true);
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		req.transaction = buildTransaction("img");
		req.message = msg;
		req.scene = friends ? SendMessageToWX.Req.WXSceneTimeline : SendMessageToWX.Req.WXSceneSession;
		msgApi.sendReq(req);
	}

	/**
	 * 微信登录获取code,code用来获取token
	 */
	public void getWechatCode(final String state, final QueryCallBack queryResult) {
		WxUserInfo info = new WxUserInfo();
		SendAuth.Req req = new SendAuth.Req();
		req.scope = "snsapi_userinfo";
		req.state = state;
		msgApi.sendReq(req);
		info.setResult(true);
		queryResult.queryCallBackMsg(info);
	}

	/**
	 * 获取微信token
	 * 
	 * @return
	 */
	public void getWechatToken(final String code, final WechatLoginCallBack tcallback) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				KeyValue keyValue1 = new KeyValue("appid", WxAppInfo.getWxInfo().getAppId());
				KeyValue keyValue2 = new KeyValue("code", code);
				String content = HttpUtil.DoContentJoint(keyValue1, keyValue2);
				HttpUtil.doGet(Addresses.URL_GET_WX_TOKEN, content, new HttpCallBack() {
					@Override
					public void callBack(String msg) {
						WxUserInfo info = new WxUserInfo();
//						Debug.e("hhhhhhhhhhhhhh "+msg);
						try {
							JSONObject obj = new JSONObject(msg);
							if (obj.getInt("result") != -1) {
								info.setOpenId(obj.getString("openid"));
				                info.setHeadImage(obj.getString("headimgurl"));
				                info.setSex(obj.getString("sex") == "2" ? "0" : "1");
				                info.setNickName(obj.getString("nickname"));
				                if (obj.has("unionid")) {
				                  info.setUnionid(obj.getString("unionid"));
//				                  setWeChatUnionid(obj.getString("unionid"));
				                } else {
				                  info.setUnionid("null");
				                }
//				                setWeChatOpenId(obj.getString("openid"));
							} else {
								info.setOpenId(TOKEN_OUT_TIME);
//								setWeChatOpenId(OPEN_ID_INIT);
							}
						} catch (JSONException e) {
							e.printStackTrace();
						}
						tcallback.callBack(info);
					}
				});
			}
		}).start();
	}

	// 启动微信SDK
	private void pay2Wx(final WxOrderInfo wxInfo) {

		TbuWxUtil.payActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				PayReq request = new PayReq();
				request.appId = WxAppInfo.getWxInfo().getAppId();
				request.partnerId = wxInfo.getWxpartnerid();
				request.packageValue = PACKAGEVALUE;
				request.prepayId = wxInfo.getWxPrepayid();
				request.nonceStr = wxInfo.getWxNonceStr();
				request.timeStamp = wxInfo.getWxTimestamp();
				request.sign = wxInfo.getWxSign();
				msgApi.sendReq(request);

			}
		});
	}

	private String createOrderInfo(String poxiaoId, String payPoint) {
		// 下单参数:charge_type,tbu_id,pay_platform,poxiao_id,game_version,
		// hsman,hstype,imei,imsi,pay_point, channel_id
		KeyValue keyValue1 = new KeyValue("charge_type", "1");// 1是微信
		KeyValue keyValue2 = new KeyValue("tbu_id", AppInfo.getTbuId());
		KeyValue keyValue3 = new KeyValue("pay_platform", "android");
		KeyValue keyValue4 = new KeyValue("poxiao_id", poxiaoId);
		KeyValue keyValue5 = new KeyValue("game_version", AppInfo.getVersion());
		KeyValue keyValue6 = new KeyValue("hsman", DeviceInfo.getProduct());
		KeyValue keyValue7 = new KeyValue("hstype", DeviceInfo.getModle().replaceAll(" ", "_"));
		KeyValue keyValue8 = new KeyValue("imei", DeviceInfo.getImei());
		KeyValue keyValue9 = new KeyValue("imsi", DeviceInfo.getImsi());
		KeyValue keyValue10 = new KeyValue("pay_point", payPoint);
		KeyValue keyValue11 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue12 = new KeyValue("request_pay_amount", "1");// 测试时的字段
		return HttpUtil.DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4, keyValue5, keyValue6, keyValue7,
				keyValue8, keyValue9, keyValue10, keyValue11, keyValue12);
	}

	private String buildTransaction(final String type) {
		return (type == null) ? String.valueOf(System.currentTimeMillis()) : type + System.currentTimeMillis();
	}

//	public String getWeChatOpenId() {
//		SharedPreferences prefer = payActivity.getSharedPreferences(WECHAT_LOGIN_OPENID, Context.MODE_PRIVATE);
//		return prefer.getString("wechat_openid", OPEN_ID_INIT);
//	}
//
//	public void setWeChatOpenId(String openid) {
//		SharedPreferences prefer = payActivity.getSharedPreferences(WECHAT_LOGIN_OPENID, Context.MODE_PRIVATE);
//		Editor edit = prefer.edit();
//		edit.putString("wechat_openid", openid);
//		edit.commit();
//	}
//	
//	public String getWeChatUnionid() {
//		SharedPreferences prefer = payActivity.getSharedPreferences(WECHAT_LOGIN_OPENID, Context.MODE_PRIVATE);
//		return prefer.getString("wechat_unionid", OPEN_ID_INIT);
//	}
//
//	public void setWeChatUnionid(String unionid) {
//		SharedPreferences prefer = payActivity.getSharedPreferences(WECHAT_LOGIN_OPENID, Context.MODE_PRIVATE);
//		Editor edit = prefer.edit();
//		edit.putString("wechat_unionid", unionid);
//		edit.commit();
//	}

	/**
	 * 清除 openID
	 */
	public void clearOpenId() {
//		setWeChatOpenId(OPEN_ID_INIT);
//		setWeChatUnionid(UNION_ID_INIT);
	}

	/**
	 * 是否安装微信
	 */
	public boolean isWxinstalled() {
		return msgApi.isWXAppInstalled();
	}
}
