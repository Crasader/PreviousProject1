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

import org.cocos2dx.cpp.chat.RecordUtil;
import org.cocos2dx.cpp.payment.Payment;
import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.WindowManager;

public class AppActivity extends Cocos2dxActivity {
	IntentFilter intentFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
	BatteryReceiver  batteryReceiver = new BatteryReceiver();
	private static int batteryPer =100; 
	//	private static AVIMClient chatClient = null;
//	private static String conversitionId = "";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
//		com.youme.im.IMEngine.init(this);     
		super.onCreate(savedInstanceState);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		Payment.init(this);
		RecordUtil.init(this);
		registerReceiver(batteryReceiver, intentFilter);
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		unregisterReceiver(batteryReceiver);
	}

	class BatteryReceiver extends BroadcastReceiver{

		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
			//判断它是否是为电量变化的Broadcast Action
			if(Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())){
				//获取当前电量
				int level = intent.getIntExtra("level", 0);
				//电量的总刻度
				int scale = intent.getIntExtra("scale", 100);
				//把它转成百分比
				batteryPer = (level*100)/scale;
			}
		}
	}

	public static String getBatteryPersent(){
		//		Debug.e("batteryPer = "+batteryPer);
		return String.valueOf(batteryPer) ;
	}

	public static void loginChatServer(final String poxiaoId){
		//		chatClient = AVIMClient.getInstance(poxiaoId);
		//		chatClient.open(new AVIMClientCallback(){
		//			@Override
		//			public void done(AVIMClient client,AVIMException e){
		//				if(e==null){
		//					Debug.e("聊天服务器连接建立成功");
		//				}
		//			}
		//		});
	}

	/**
	 * 建立聊天室
	 * @param poxiaoId
	 */
	public static void createRoom(final String poxiaoId){
		//		chatClient = AVIMClient.getInstance(poxiaoId);
		//		chatClient.open(new AVIMClientCallback(){
		//
		//			@Override
		//			public void done(AVIMClient client,AVIMException e){
		//				if(e==null){
		//					//登录成功
		//					//创建一个 名为 "ShangHaiMahjong"的暂态对话
		//					client.createConversation(Collections.<String>emptyList(),"ShangHaiMahjong"+poxiaoId,null,true,
		//							new AVIMConversationCreatedCallback(){
		//						@Override
		//						public void done(AVIMConversation conv,AVIMException e){
		//							Debug.e("成功创建了一个聊天室");
		//							conversitionId = conv.getConversationId();
		//						}
		//					});
		//				}
		//			}
		//		});
	}

	public static void addMenber(final String myPoxiaoId,final String tarPoxiaoId){
		//		chatClient = AVIMClient.getInstance(myPoxiaoId);
		//		chatClient.open(new AVIMClientCallback() {
		//			@Override
		//			public void done(AVIMClient client, AVIMException e) {
		//				if (e == null) {
		//					//登录成功
		//					final AVIMConversation conv = client.getConversation(conversitionId);
		//					conv.join(new AVIMConversationCallback() {
		//						@Override
		//						public void done(AVIMException e) {
		//							if (e == null) {
		//								//加入成功
		//								conv.addMembers(Arrays.asList(tarPoxiaoId), new AVIMConversationCallback() {
		//									@Override
		//									public void done(AVIMException e) {
		//										Debug.i("加入用户成功：用户："+tarPoxiaoId);
		//									}
		//								});
		//							}
		//						}
		//					});
		//				}
		//			}
		//		});
	}

	public static void sendChatInfo(String poxiaoId,final String sendMsg){
		//		chatClient = AVIMClient.getInstance(poxiaoId);
		//		chatClient.open(new AVIMClientCallback() {
		//			@Override
		//			public void done(AVIMClient client, AVIMException e) {
		//				if (e == null) {
		//					//登录成功
		//					final AVIMConversation conversation = client.getConversation(conversitionId);
		//					conversation.join(new AVIMConversationCallback() {
		//						@Override
		//						public void done(AVIMException e) {
		//							if (e == null) {
		//								AVIMTextMessage msg = new AVIMTextMessage();
		//								msg.setText(sendMsg);
		//								// 发送消息
		//								conversation.sendMessage(msg, new AVIMConversationCallback() {
		//
		//									@Override
		//									public void done(AVIMException e) {
		//										// TODO Auto-generated method stub
		//										Debug.e("发送消息");
		//									}
		//								});
		//
		//							}
		//						}
		//					});
		//				}
		//			}
		//		});
	}
	
}
