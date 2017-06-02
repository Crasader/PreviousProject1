package com.tbu.wx.http;

public class Addresses {

	public static final String URL_ORDER = "http://web.5278-mobi.com/pay!generateOrd.action";//支付下单
	public static final String URL_ORDER_THIRD = "http://web.5278-mobi.com/pay!generatehtfOrd.action";//支付下单

	
	public static final String URL_CALLBACK = "http://web.5278-mobi.com:1111/pay!ordCallback.action";//回调服务器
	public static final String URL_QUERY_ORDER ="http://web.5278-mobi.com:1111/pay!findOrd.action";//查询订单
	public static final String URL_CLOSE_ORDER = "http://106.75.135.78:1801/weixin/pay/closeorder";//关闭订单
	public static final String URL_GET_WX_TOKEN ="http://web.5278-mobi.com:1111/pay!getWxAccessToken.action";
	public static final String URL_REFESH_WX_TOKEN ="http://web.5278-mobi.com:1111/pay!refreshsWxAccessToken.action";
	public static final String URL_CHECK_TOKEN_OUTTIME ="http://web.5278-mobi.com:1111/pay!getIfExpire.action";
}
