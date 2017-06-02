package com.tbu.wx.http.data;

public class WxOrderInfo {
    
	private String pxOrderId;
	private String wxPrepayid;
	private String wxSign;
	private String wxTimestamp;
	private String wxNonceStr;
	private String wxpartnerid;

	
	public String getWxpartnerid() {
		return wxpartnerid;
	}

	public void setWxpartneri(String wxpartnerid) {
		this.wxpartnerid = wxpartnerid;
	}
	
	public String getPxOrderId() {
		return pxOrderId;
	}

	public void setPxOrderId(String pxOrderId) {
		this.pxOrderId = pxOrderId;
	}

	public String getWxPrepayid() {
		return wxPrepayid;
	}

	public void setWxPrepayid(String wxPrepayid) {
		this.wxPrepayid = wxPrepayid;
	}

	public String getWxSign() {
		return wxSign;
	}

	public void setWxSign(String wxSign) {
		this.wxSign = wxSign;
	}

	public String getWxTimestamp() {
		return wxTimestamp;
	}

	public void setWxTimestamp(String wxTimestamp) {
		this.wxTimestamp = wxTimestamp;
	}

	public String getWxNonceStr() {
		return wxNonceStr;
	}

	public void setWxNonceStr(String wxNonceStr) {
		this.wxNonceStr = wxNonceStr;
	}

}
