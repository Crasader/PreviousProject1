package org.cocos2dx.cpp.chat.recordAudio;

/**
 * 语音上传
 * @author Rex.lsf
 * 有问题请联系QQ:271809781
 * 
 * add by tanweijiang
 * qq: 704177907
 */
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import org.cocos2dx.cpp.payment.JniPayCallbackHelper;

import com.tbu.androidtools.Debug;

import android.app.Activity;
import android.gesture.GestureOverlayView;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

public class AudioRecorderManager {

	/*
	 * 录音底层类
	 */
	private AudioRecorder mr; // 录音底层
	private MediaPlayer mediaPlayer; // 声音播放类

	private static Activity appActivity;

	//	private TextView luyin_txt, luyin_path, record_memo, player_memo;
	private Thread recordThread; // 录音计时线程

	private static int MAX_TIME = 0; // 最长录制时间，单位秒，0为无时间限制
	private static int MIX_TIME = 1; // 最短录制时间，单位秒，0为无时间限制，建议设为1
	private static int RECODE_STATE = 0; // 录音的状态
	private static int RECORD_NO = 0; // 不在录音
	private static int RECORD_ING = 1; // 正在录音
	private static int RECODE_ED = 2; // 完成录音
	public static float recodeTime = 0.0f; // 录音的时间
	private static double voiceValue = 0.0; // 麦克风获取的音量值

	private static boolean playState = false; // 播放状态
	private String date = "";

	public void init(Activity activity) {
		appActivity = activity;
	}

	// 开始录音 录音按钮按下调用 btnDown
	public void beginRecordAudio() {
		if (RECODE_STATE != RECORD_ING) {
			date = new SimpleDateFormat("yy-MM-dd-HH-mm-ss",
					Locale.getDefault()).format(new Date());
			mr = new AudioRecorder();
			RECODE_STATE = RECORD_ING;
			try {
				mr.start();
			} catch (IOException e) {
				e.printStackTrace();
			}
			mythread();
		}
	}

	// 录音结束 录音按钮弹起调用 btnUp
	public void endRecordAudio() {
		if (RECODE_STATE == RECORD_ING) {
			RECODE_STATE = RECODE_ED;
			try {
				mr.stop();
				voiceValue = 0.0;
			} catch (IOException e) {
				e.printStackTrace();
			}

			if (recodeTime < MIX_TIME) {
				appActivity.runOnUiThread(new Runnable() {
					public void run() {
						Toast.makeText(appActivity, "说话时间太短", Toast.LENGTH_SHORT).show();
					}
				});
				RECODE_STATE = RECORD_NO;
				File file = new File(getAmrPath());
				file.delete();
			} else {
				// 录音完成!点击重新录音
			}
		}
	}

	// 播放录音
	public void playAudio() {

		if (!playState) {
			mediaPlayer = new MediaPlayer();
			try {
				mediaPlayer.setDataSource(getAmrPath());
				mediaPlayer.prepare();
				mediaPlayer.start();
				playState = true;
				// 设置播放结束时监听
				mediaPlayer.setOnCompletionListener(new OnCompletionListener() {

					@Override
					public void onCompletion(MediaPlayer mp) {
						if (playState) {
							playState = false;
						}
					}
				});
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalStateException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}

		} else {
			if (mediaPlayer.isPlaying()) {
				mediaPlayer.stop();
				playState = false;
			} else {
				playState = false;
			}
		}
	}

	// 删除文件 录音
	public void deleteFile() {
		File file = new File(getAmrPath());
		file.delete();
	}


	// 获取文件手机路径
	public String getAmrPath() {
		Debug.e("getAmrPath = "+JniPayCallbackHelper.getWriteablePath());
//		File file = new File(JniPayCallbackHelper.getWriteablePath(), "/"
//				+ date + ".amr");
		File file = new File(Environment.getExternalStorageDirectory(), "/"
				+ date + ".amr");
		Debug.e("getAmrPath = "+file.getAbsolutePath());
		return file.getAbsolutePath();
	}

	// 录音计时线程
	public void mythread() {
		recordThread = new Thread(ImgThread);
		recordThread.start();
	}

	// 录音线程
	public Runnable ImgThread = new Runnable() {

		@Override
		public void run() {
			recodeTime = 0.0f;
			while (RECODE_STATE == RECORD_ING) {
				if (recodeTime >= MAX_TIME && MAX_TIME != 0) {
					imgHandle.sendEmptyMessage(0);
				} else {
					try {
						Thread.sleep(200);
						recodeTime += 0.2;
						if (RECODE_STATE == RECORD_ING) {
							voiceValue = mr.getAmplitude();
							imgHandle.sendEmptyMessage(1);
						}
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}

		Handler imgHandle = new Handler() {
			@Override
			public void handleMessage(Message msg) {

				switch (msg.what) {
				case 0:
					// 录音超过15秒自动停止
					if (RECODE_STATE == RECORD_ING) {
						RECODE_STATE = RECODE_ED;

						try {
							mr.stop();
							voiceValue = 0.0;
						} catch (IOException e) {
							e.printStackTrace();
						}

						if (recodeTime < 1.0) {
							appActivity.runOnUiThread(new Runnable() {
								public void run() {
									Toast.makeText(appActivity, "说话时间太短", Toast.LENGTH_SHORT).show();
								}
							});
							
							RECODE_STATE = RECORD_NO;
						} else {
							//	录音完成!点击重新录音
						}
					}
					break;
				case 1:
					//setDialogImage();
					break;
				default:
					break;
				}
			}
		};
	};

}