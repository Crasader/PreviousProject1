package com.poxiao.mahjong.wxapi;

import org.cocos2dx.cpp.payment.JniPayCallbackHelper;
import org.cocos2dx.cpp.payment.Payment;

import com.tbu.androidtools.Debug;
import com.tbu.wx.http.callback.WechatLoginCallBack;
import com.tbu.wx.util.WxAppInfo;
import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelmsg.SendAuth;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler {

	private IWXAPI api;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		api = WXAPIFactory.createWXAPI(this, WxAppInfo.getWxInfo().getAppId());
		api.handleIntent(getIntent(), this);
	}

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
		api.handleIntent(intent, this);
	}

	@Override
	public void onReq(BaseReq req) {

	}

	@Override
	public void onResp(BaseResp resp) {
		if (ConstantsAPI.COMMAND_PAY_BY_WX == resp.getType()) {
			if (resp.errCode == BaseResp.ErrCode.ERR_OK) {
				Payment.queryPayResult();
			} else {
				JniPayCallbackHelper.eventCallBack(Integer.valueOf(Payment.eventId), 0);
			}
		} else if (ConstantsAPI.COMMAND_SENDAUTH == resp.getType()) {

			SendAuth.Resp authresp = (SendAuth.Resp) resp;
			if (BaseResp.ErrCode.ERR_OK == authresp.errCode) {
				if (Payment.getWeChatState().equals(authresp.state)) {
					Payment.getWechatToken(authresp.code, new WechatLoginCallBack() {
						@Override
						public void callBack(String openid) {
							JniPayCallbackHelper.loginThirdPlatform(openid);
						}
					});
				} else {
					Debug.e("错误的微信请求参数state");
				}

			} else if (BaseResp.ErrCode.ERR_AUTH_DENIED == authresp.errCode) {
				// 用户拒绝授权

			} else if (BaseResp.ErrCode.ERR_USER_CANCEL == authresp.errCode) {
				// 用户取消

			}
		} else if (ConstantsAPI.COMMAND_SENDMESSAGE_TO_WX == resp.getType()) {

		}
		WXEntryActivity.this.finish();
	}
}