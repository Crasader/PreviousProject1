package org.cocos2dx.cpp.chat;

import org.cocos2dx.cpp.chat.recordAudio.AudioRecorderManager;

import com.tbu.androidtools.Debug;

import android.app.Activity;

public class RecordUtil {

	private static Activity activity;
	private static AudioRecorderManager audioManager;

	public static void init(Activity activity) {
		RecordUtil.activity = activity;
		audioManager = new AudioRecorderManager();
		audioManager.init(RecordUtil.activity);	
	}


	/**
	 * 开始录音
	 */
	public static void beginRecordAudio() {
		Debug.e("RecordUtil->beginRecordAudio");
		try {
			audioManager.beginRecordAudio();	
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

	/**
	 * 结束录音
	 */
	public static void endRecordAudio() {
		Debug.e("RecordUtil->endRecordAudio");
		try {
			audioManager.endRecordAudio();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

	/**
	 * 播放录音
	 */
	public static void playAudio() {
		Debug.e("RecordUtil->playAudio");
		audioManager.playAudio();
	}

	/**
	 *  删除录音
	 */
	public static void deleteFile() {
		Debug.e("RecordUtil->deleteFile");
		audioManager.deleteFile();
	}

	/**
	 * 获取录音路径
	 */
	public static String getRecordFilePath() {
		Debug.e("RecordUtil->getRecordFilePath");  
		return audioManager.getAmrPath();
	}


}
