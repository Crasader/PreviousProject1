package org.cocos2dx.cpp;

//import org.cocos2dx.cpp.chat.CustomMessageHandler;
//
//import com.avos.avoscloud.AVOSCloud;
//import com.avos.avoscloud.im.v2.AVIMMessageManager;
//import com.avos.avoscloud.im.v2.AVIMTypedMessage;
//import com.avos.avoscloud.im.v2.messages.AVIMTextMessage;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;

import android.app.Application;
import android.content.pm.PackageManager;

public class MahjongAplication extends Application{
	
	private static MahjongAplication instance;
	
	@Override
	public void onCreate() {
		super.onCreate();
		Debug.i("MahjongAplication onCreate");
		instance = this;
		TbuAndroidTools.init(getApplicationContext());
		 // 初始化参数依次为 this, AppId, AppKey
//        AVOSCloud.initialize(this,"sR4STlNl0O4DjvziXzOpL57P-gzGzoHsz","jLfV5fwXLMiRMPM7hPgQJuPr");
//        AVIMMessageManager.registerMessageHandler(AVIMTypedMessage.class,new CustomMessageHandler());//注册消息监听
//        AVOSCloud.setDebugLogEnabled(true);//调试日志
	}
	
	public static MahjongAplication getInstance(){		
		return instance;
	}
	
	public boolean hasAudioPermission(){
		PackageManager pm = getPackageManager();  
        boolean permission = (PackageManager.PERMISSION_GRANTED ==   
                pm.checkPermission("android.permission.RECORD_AUDIO", "packageName"));  
        if (permission) {  
            return true;
        }
        return false;
	}
	
	
}
