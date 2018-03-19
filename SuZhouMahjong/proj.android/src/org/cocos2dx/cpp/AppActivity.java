/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import java.util.Map;

import org.cocos2dx.cpp.chat.RecordUtil;
import org.cocos2dx.cpp.payment.JniPayCallbackHelper;
import org.cocos2dx.cpp.payment.Payment;
import org.cocos2dx.lib.Cocos2dxActivity;

import com.baidu.location.BDLocation;
import com.baidu.location.BDLocationListener;
import com.baidu.location.LocationClient;
import com.baidu.location.LocationClientOption;
import com.baidu.location.LocationClientOption.LocationMode;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.wx.wechat.TbuWxUtil;
import com.zxinsight.MLink;
import com.zxinsight.MWConfiguration;
import com.zxinsight.MagicWindowSDK;
import com.zxinsight.Session;
import com.zxinsight.mlink.MLinkCallback;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.text.ClipboardManager;
import android.view.WindowManager;

public class AppActivity extends Cocos2dxActivity {
	IntentFilter intentFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
	BatteryReceiver batteryReceiver = new BatteryReceiver();
	private static int batteryPer = 100;
	private static Activity myActivity;

	public LocationClient mLocationClient = null;
	private MyLocationListener myListener = new MyLocationListener();
	public class MyLocationListener implements BDLocationListener{
	    @Override
	    public void onReceiveLocation(BDLocation location){
	        //此处的BDLocation为定位结果信息类，通过它的各种get方法可获取定位相关的全部结果
	        //以下只列举部分获取经纬度相关（常用）的结果信息
	        //更多结果信息获取说明，请参照类参考中BDLocation类中的说明
				
	        double latitude = location.getLatitude();    //获取纬度信息
	        double longitude = location.getLongitude();    //获取经度信息
	        
	        TbuWxUtil.getInstance().setPlayerLocationLongitude(String.valueOf(longitude));
	        TbuWxUtil.getInstance().setPlayerLocationLatitude(String.valueOf(latitude));
	        
//	        float radius = location.getRadius();    //获取定位精度，默认值为0.0f
				
//	        String coorType = location.getCoorType();
	        //获取经纬度坐标类型，以LocationClientOption中设置过的坐标类型为准
				
//	        int errorCode = location.getLocType();
	        //获取定位类型、定位错误返回码，具体信息可参照类参考中BDLocation类中的说明
	        Debug.e("地理位置经纬度("+longitude+","+latitude+")");
	    }
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		Payment.init(this);
		RecordUtil.init(this);
		registerReceiver(batteryReceiver, intentFilter);
		MWConfiguration config = new MWConfiguration(this);
		MagicWindowSDK.initSDK(config);
		myActivity = this;
		registerForMLinkCallback();
		MLink.getInstance(AppActivity.this).deferredRouter();

		Uri mLink = getIntent().getData();
		if (mLink != null) {
			MLink.getInstance(this).router(mLink);
		} else {
			MLink.getInstance(this).checkYYB();
		}
	    mLocationClient = new LocationClient(getApplicationContext());     
	    //声明LocationClient类
	    mLocationClient.registerLocationListener(myListener);    
	    //注册监听函数
	    LocationClientOption option = new LocationClientOption();

	    option.setLocationMode(LocationMode.Hight_Accuracy);
	    //可选，设置定位模式，默认高精度
	    //LocationMode.Hight_Accuracy：高精度；
	    //LocationMode. Battery_Saving：低功耗；
	    //LocationMode. Device_Sensors：仅使用设备；
	    	
	    option.setCoorType("bd09ll");
	    //可选，设置返回经纬度坐标类型，默认gcj02
	    //gcj02：国测局坐标；
	    //bd09ll：百度经纬度坐标；
	    //bd09：百度墨卡托坐标；
	    //海外地区定位，无需设置坐标类型，统一返回wgs84类型坐标
	     	
	    option.setScanSpan(1000);
	    //可选，设置发起定位请求的间隔，int类型，单位ms
	    //如果设置为0，则代表单次定位，即仅定位一次，默认为0
	    //如果设置非0，需设置1000ms以上才有效
	    	
	    option.setOpenGps(true);
	    //可选，设置是否使用gps，默认false
	    //使用高精度和仅用设备两种定位模式的，参数必须设置为true
	    	
	    option.setLocationNotify(true);
	    //可选，设置是否当GPS有效时按照1S/1次频率输出GPS结果，默认false
	    	
	    option.setIgnoreKillProcess(false);
	    //可选，定位SDK内部是一个service，并放到了独立进程。
	    //设置是否在stop的时候杀死这个进程，默认（建议）不杀死，即setIgnoreKillProcess(true)
	    	
	    option.SetIgnoreCacheException(false);
	    //可选，设置是否收集Crash信息，默认收集，即参数为false

	    option.setWifiCacheTimeOut(5*60*1000);
	    //可选，7.2版本新增能力
	    //如果设置了该接口，首次启动定位时，会先判断当前WiFi是否超出有效期，若超出有效期，会先重新扫描WiFi，然后定位
	    	
	    option.setEnableSimulateGps(false);
	    //可选，设置是否需要过滤GPS仿真结果，默认需要，即参数为false
	    	
	    mLocationClient.setLocOption(option);
	    //mLocationClient为第二步初始化过的LocationClient对象
	    //需将配置好的LocationClientOption对象，通过setLocOption方法传递给LocationClient对象使用
	    //更多LocationClientOption的配置，请参照类参考中LocationClientOption类的详细说明
	    mLocationClient.start();
	}

	private static void registerForMLinkCallback() {
		MLink mLink = MagicWindowSDK.getMLink();
		mLink.registerDefault(new MLinkCallback() {
			@Override
			public void execute(Map<String, String> paramMap, Uri uri, Context context) {
				// todo: 获取动态参数,用来处理
				String id = "";
				if (paramMap != null) {
					id = paramMap.get("roomid");
				} else if (uri != null) {
					id = uri.getQueryParameter("roomid");
				}
				Debug.e("**********************id = " + id);
				if (!id.isEmpty()) {
					JniPayCallbackHelper.addRoomByInvited(id);
				}
			}
		});

	}

	@Override
	public void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		this.setIntent(intent);

		Uri mLink = intent.getData();
		if (mLink != null) {
			Debug.e(mLink.toString());
		} else {
			MLink.getInstance(this).checkYYB();
		}
	}

	@Override
	protected void onPause() {
		Session.onPause(this);
		super.onPause();
	}

	@Override
	protected void onResume() {
		Session.onResume(this);
		super.onResume();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		unregisterReceiver(batteryReceiver);
	}

	class BatteryReceiver extends BroadcastReceiver {

		@Override
		public void onReceive(Context context, Intent intent) {
			// 判断它是否是为电量变化的Broadcast Action
			if (Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())) {
				// 获取当前电量
				int level = intent.getIntExtra("level", 0);
				// 电量的总刻度
				int scale = intent.getIntExtra("scale", 100);
				// 把它转成百分比
				batteryPer = (level * 100) / scale;
			}
		}
	}

	public static String getLongitude(){
		return TbuWxUtil.getInstance().getPlayerLocationLongitude();
	} 
	
	public static String getLatitude(){
	    return  TbuWxUtil.getInstance().getPlayerLocationLatitude();
	}
	
	public static String getBatteryPersent() {
		// Debug.e("batteryPer = "+batteryPer);
		return String.valueOf(batteryPer);
	}

	public static void copyToPasteboard(final String msg) {
		Runnable runnable = new Runnable() {
			public void run() {
				ClipboardManager mClipboardManager = (ClipboardManager) myActivity.getSystemService(CLIPBOARD_SERVICE);
				mClipboardManager.setText(msg);
			}
		};
		myActivity.runOnUiThread(runnable);

	}

	public static boolean hasAudioPermission() {
		PackageManager pm = myActivity.getPackageManager();
		boolean permission = (PackageManager.PERMISSION_GRANTED == pm.checkPermission("android.permission.RECORD_AUDIO",
				"packageName"));
		if (permission) {
			return true;
		}
		return false;
	}

	public static void downLoadApk(String url) {
		Intent intent = new Intent();
		intent.setAction(Intent.ACTION_VIEW);
		Uri content_url = Uri.parse(url);
		intent.setData(content_url);
		myActivity.startActivity(Intent.createChooser(intent, "请选择推荐浏览器"));
	}

	public static String getAndroidAppVersion() {
		return AppInfo.getVersion();
	}
}
