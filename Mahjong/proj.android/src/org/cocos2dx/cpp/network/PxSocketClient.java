package org.cocos2dx.cpp.network;

import com.vilyever.socketclient.SocketClient;
import com.vilyever.socketclient.helper.SocketClientDelegate;
import com.vilyever.socketclient.helper.SocketPacketHelper;
import com.vilyever.socketclient.helper.SocketResponsePacket;
import com.vilyever.socketclient.util.CharsetUtil;

import android.os.AsyncTask;
import android.support.annotation.NonNull;
import android.util.Log;

/**
 * TestClient Created by vilyever on 2016/7/26. Feature:
 */
public class PxSocketClient {
	private static PxSocketClient instance;
	private SocketClient localSocketClient = null;

	public static PxSocketClient getInstance() {
		if (null == instance) {
			instance = new PxSocketClient();
		}
		return instance;
	}

	/* Constructors */
	private PxSocketClient() {
		// 私有构造
	}

	/* Public Methods */
	public void connect(String ip, String port) {
		getLocalSocketClient(ip, port).connect();
	}

	public void sendDataSever(String msg) {
		if (localSocketClient != null) {
			Log.i("AndroidSocket", "向服务端发送数据:" + msg);
			localSocketClient.sendData(CharsetUtil.stringToData(msg, CharsetUtil.UTF_8));
		}
	}
	
	public void startHeartBeat(String sendHeart,String recieveHeart){
		setupConstantHeartBeat(localSocketClient, sendHeart, recieveHeart);
	}

	private SocketClient getLocalSocketClient(String ip, String port) {
		if (localSocketClient == null) {
			localSocketClient = new SocketClient();
			// 设置读取规则
			localSocketClient.getSocketPacketHelper().setReadStrategy(SocketPacketHelper.ReadStrategy.AutoReadToTrailer);
			localSocketClient.getSocketPacketHelper().setReceiveTrailerData(CharsetUtil.stringToData("\r\n", CharsetUtil.UTF_8));
			// 设置远程连接端口
			localSocketClient.getAddress().setRemoteIP(ip); // 远程端IP地址
			localSocketClient.getAddress().setRemotePort(port); // 远程端端口号
			localSocketClient.getAddress().setConnectionTimeout(15 * 1000); // 连接超时时长，单位毫秒
			// 设置编码格式
			localSocketClient.setCharsetName(CharsetUtil.UTF_8); // 设置编码为UTF-8
			// 设置自动发送的心跳包信息
			// setupConstantHeartBeat(localSocketClient);
			// 客户端代理
			localSocketClient.registerSocketClientDelegate(new SocketClientDelegate() {
				@Override
				public void onConnected(SocketClient client) {
					Log.i("AndroidSocket", "PxSocketClient: onConnected");
				}

				@Override
				public void onDisconnected(final SocketClient client) {
					Log.i("AndroidSocket", "PxSocketClient: onDisconnected");
					new AsyncTask<Void, Void, Void>() {
						@Override
						protected Void doInBackground(Void... params) {
							try {
								Thread.sleep(3 * 1000);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}

							client.connect();

							return null;
						}

						@Override
						protected void onPostExecute(Void aVoid) {
							super.onPostExecute(aVoid);

						}
					}.execute();
				}

				@Override
				public void onResponse(final SocketClient client, @NonNull SocketResponsePacket responsePacket) {
					Log.i("AndroidSocket","PxSocketClient: onResponse: " + responsePacket.getMessage());
					if(null!=responsePacket.getMessage())
						JniSocketCallback.dataRecieve(responsePacket.getMessage());
					if (responsePacket.isHeartBeat()) {
						return;
					}
//					new AsyncTask<Void, Void, Void>() {
//						@Override
//						protected Void doInBackground(Void... params) {
//							try {
//								Thread.sleep(3 * 1000);
//							} catch (InterruptedException e) {
//								e.printStackTrace();
//							}
//
//							client.sendString("client on " + System.currentTimeMillis());
//
//							try {
//								Thread.sleep(3 * 1000);
//							} catch (InterruptedException e) {
//								e.printStackTrace();
//							}
//							Log.e("AndroidSocket", "Socket连接断开 005");
//							client.disconnect();
//
//							return null;
//						}
//
//						@Override
//						protected void onPostExecute(Void aVoid) {
//							super.onPostExecute(aVoid);
//
//						}
//					}.execute();
				}
			});
		}
		return localSocketClient;
	}

	private void setupConstantHeartBeat(SocketClient socketClient, String heartBeatSend, String heartBeatRecive) {
		Log.e("AndroidSocket", "PxSocketClient: setupConstantHeartBeat ="+heartBeatSend);
		Log.e("AndroidSocket", "PxSocketClient: setupConstantHeartBeat ="+heartBeatRecive);
		/**
		 * 设置自动发送的心跳包信息
		 */
		socketClient.getHeartBeatHelper()
				.setDefaultSendData(CharsetUtil.stringToData(heartBeatSend, CharsetUtil.UTF_8));
		/**
		 * 设置远程端发送到本地的心跳包信息内容，用于判断接收到的数据包是否是心跳包 通过
		 * {@link SocketResponsePacket#isHeartBeat()} 查看数据包是否是心跳包
		 */
		socketClient.getHeartBeatHelper()
				.setDefaultReceiveData(CharsetUtil.stringToData(heartBeatRecive, CharsetUtil.UTF_8));
		socketClient.getHeartBeatHelper().setHeartBeatInterval(5 * 1000); // 设置自动发送心跳包的间隔时长，单位毫秒
		socketClient.getHeartBeatHelper().setSendHeartBeatEnabled(true); // 设置允许自动发送心跳包，此值默认为false
	}

}