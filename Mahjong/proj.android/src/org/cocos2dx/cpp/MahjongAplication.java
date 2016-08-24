package org.cocos2dx.cpp;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.TbuAndroidTools;

import android.app.Application;

public class MahjongAplication extends Application{
	
	private static MahjongAplication instance;
	
	@Override
	public void onCreate() {
		super.onCreate();
		Debug.i("MahjongAplication onCreate");
		instance = this;
		TbuAndroidTools.init(getApplicationContext());
	}
	
	public static MahjongAplication getInstance(){		
		return instance;
	}
	
}
