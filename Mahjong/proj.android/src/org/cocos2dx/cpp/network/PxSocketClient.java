package org.cocos2dx.cpp.network;

import java.util.Arrays;

import com.vilyever.socketclient.SocketClient;
import com.vilyever.socketclient.helper.SocketClientDelegate;
import com.vilyever.socketclient.helper.SocketClientReceivingDelegate;
import com.vilyever.socketclient.helper.SocketClientSendingDelegate;
import com.vilyever.socketclient.helper.SocketPacket;
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
			localSocketClient.sendString(msg);
		}
	}

	private SocketClient getLocalSocketClient(String ip, String port) {
		if (localSocketClient == null) {
			localSocketClient = new SocketClient();
			// 设置远程连接端口
			localSocketClient.getAddress().setRemoteIP(ip); // 远程端IP地址
			localSocketClient.getAddress().setRemotePort(port); // 远程端端口号
			localSocketClient.getAddress().setConnectionTimeout(15 * 1000); // 连接超时时长，单位毫秒
			// 设置编码格式
			localSocketClient.setCharsetName(CharsetUtil.UTF_8); // 设置编码为UTF-8
			// 设置自动发送的心跳包信息
			setupConstantHeartBeat(localSocketClient);
			setupReadByLengthForSender(localSocketClient);
			setupReadByLengthForReceiver(localSocketClient);
			// 客户端代理
			localSocketClient.registerSocketClientDelegate(new SocketClientDelegate() {
				@Override
				public void onConnected(SocketClient client) {
					Log.e("AndroidSocket", "PxSocketClient: onConnected");
					if (client.getSocketPacketHelper().getReadStrategy() == SocketPacketHelper.ReadStrategy.Manually) {
						client.readDataToLength(CharsetUtil.stringToData("Server accepted", CharsetUtil.UTF_8).length);
					}
				}

				@Override
				public void onDisconnected(final SocketClient client) {
					Log.e("AndroidSocket", "PxSocketClient: onDisconnected");
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
					Log.e("AndroidSocket",
							"PxSocketClient: onResponse: " + responsePacket.hashCode() + " 【"
									+ responsePacket.getMessage() + "】 " + " isHeartBeat: "
									+ responsePacket.isHeartBeat() + " " + Arrays.toString(responsePacket.getData()));
					if (responsePacket.isHeartBeat()) {
						return;
					}
					new AsyncTask<Void, Void, Void>() {
						@Override
						protected Void doInBackground(Void... params) {
							try {
								Thread.sleep(3 * 1000);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}

							client.sendString("client on " + System.currentTimeMillis());

							try {
								Thread.sleep(3 * 1000);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}

							client.disconnect();

							return null;
						}

						@Override
						protected void onPostExecute(Void aVoid) {
							super.onPostExecute(aVoid);

						}
					}.execute();
				}
			});
			// 发送代理
			this.localSocketClient.registerSocketClientSendingDelegate(new SocketClientSendingDelegate() {

				@Override
				public void onSendPacketBegin(SocketClient client, SocketPacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onSendPacketBegin: " + packet.hashCode() + "   "
							+ Arrays.toString(packet.getData()));
				}

				@Override
				public void onSendPacketCancel(SocketClient client, SocketPacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onSendPacketCancel: " + packet.hashCode());
				}

				@Override
				public void onSendingPacketInProgress(SocketClient client, SocketPacket packet, float progress,
						int sendedLength) {
					// Log.e("AndroidSocket", "SocketClient:
					// onSendingPacketInProgress: " + packet.hashCode() + " : "
					// + progress + " : " + sendedLength);
				}

				@Override
				public void onSendPacketEnd(SocketClient client, SocketPacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onSendPacketEnd: " + packet.hashCode());
				}
			});
			// 接收代理
			this.localSocketClient.registerSocketClientReceiveDelegate(new SocketClientReceivingDelegate() {
				@Override
				public void onReceivePacketBegin(SocketClient client, SocketResponsePacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onReceivePacketBegin: " + packet.hashCode());
				}

				@Override
				public void onReceivePacketEnd(SocketClient client, SocketResponsePacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onReceivePacketEnd: " + packet.hashCode());
					Log.e("AndroidSocket", "onReceivePacketEnd = "+packet.getMessage());
				}

				@Override
				public void onReceivePacketCancel(SocketClient client, SocketResponsePacket packet) {
					Log.e("AndroidSocket", "PxSocketClient: onReceivePacketCancel: " + packet.hashCode());
				}

				@Override
				public void onReceivingPacketInProgress(SocketClient client, SocketResponsePacket packet,
						float progress, int receivedLength) {
					Log.e("AndroidSocket", "PxSocketClient: onReceivingPacketInProgress: " + packet.hashCode() + " : "
							+ progress + " : " + receivedLength);
				}
			});
		}
		return localSocketClient;
	}

	private void setupConstantHeartBeat(SocketClient socketClient) {
		/**
		 * 设置自动发送的心跳包信息
		 */
		socketClient.getHeartBeatHelper().setDefaultSendData(
				CharsetUtil.stringToData("{\"code\":\"1\",\"poxiaoId\":\"201611180934568305x0\"}", CharsetUtil.UTF_8));
		/**
		 * 设置远程端发送到本地的心跳包信息内容，用于判断接收到的数据包是否是心跳包 通过
		 * {@link SocketResponsePacket#isHeartBeat()} 查看数据包是否是心跳包
		 */
		socketClient.getHeartBeatHelper().setDefaultReceiveData(
				CharsetUtil.stringToData("{\"code\":\"2\",\"poxiaoId\":\"201611180934568305x0\"}", CharsetUtil.UTF_8));
		socketClient.getHeartBeatHelper().setHeartBeatInterval(5 * 1000); // 设置自动发送心跳包的间隔时长，单位毫秒
		socketClient.getHeartBeatHelper().setSendHeartBeatEnabled(true); // 设置允许自动发送心跳包，此值默认为false
	}

	private void setupReadByLengthForSender(SocketClient socketClient) {
		/**
		 * 设置包长度转换器 即每次发送数据时，将包头以外的数据长度转换为特定的byte[]发送个远程端用于解析还需要读取多少长度的数据
		 *
		 * 例：socketClient.sendData(new byte[]{0x01, 0x02})的步骤为 1.
		 * socketClient向远程端发送包头（如果设置了包头信息） 2. socketClient要发送的数据为{0x01,
		 * 0x02}，长度为2（若设置了包尾，还需加上包尾的字节长度），通过此转换器将int类型的2转换为4字节的byte[]，
		 * 远程端也照此算法将4字节的byte[]转换为int值 3. socketClient向远程端发送转换后的长度信息byte[] 4.
		 * socketClient向远程端发送正文数据{0x01, 0x02} 5. socketClient向远程端发送包尾（如果设置了包尾信息）
		 *
		 * 此转换器用于第二步
		 *
		 * 使用
		 * {@link com.vilyever.socketclient.helper.SocketPacketHelper.ReadStrategy.AutoReadByLength}
		 * 必须设置此项 用于分隔多条消息
		 */
		socketClient.getSocketPacketHelper()
				.setSendPacketLengthDataConvertor(new SocketPacketHelper.SendPacketLengthDataConvertor() {
					@Override
					public byte[] obtainSendPacketLengthDataForPacketLength(SocketPacketHelper helper,
							int packetLength) {
						/**
						 * 简单将int转换为byte[]
						 */
						byte[] data = new byte[4];
						data[3] = (byte) (packetLength & 0xFF);
						data[2] = (byte) ((packetLength >> 8) & 0xFF);
						data[1] = (byte) ((packetLength >> 16) & 0xFF);
						data[0] = (byte) ((packetLength >> 24) & 0xFF);
						return data;
					}
				});

		/**
		 * 设置分段发送数据长度 即在发送指定长度后通过
		 * {@link SocketClientSendingDelegate#onSendingPacketInProgress(SocketClient, SocketPacket, float, int)}
		 * 回调当前发送进度 注意：回调过于频繁可能导致设置UI过于频繁从而导致主线程卡顿
		 *
		 * 若无需进度回调可删除此二行，删除后仍有【发送开始】【发送结束】的回调
		 */
//		socketClient.getSocketPacketHelper().setSendSegmentLength(8); // 设置发送分段长度，单位byte
//		socketClient.getSocketPacketHelper().setSendSegmentEnabled(true); // 设置允许使用分段发送，此值默认为false

		/**
		 * 设置发送超时时长 在发送每个数据包时，发送每段数据的最长时间，超过后自动断开socket连接 通过设置分段发送
		 * {@link SocketPacketHelper#setSendSegmentEnabled(boolean)}
		 * 可避免发送大数据包时因超时断开，
		 *
		 * 若无需限制发送时长可删除此二行
		 */
//		socketClient.getSocketPacketHelper().setSendTimeout(30 * 1000); // 设置发送超时时长，单位毫秒
//		socketClient.getSocketPacketHelper().setSendTimeoutEnabled(true); // 设置允许使用发送超时时长，此值默认为false
	}

	private void setupReadByLengthForReceiver(SocketClient socketClient) {
		  /**
         * 设置读取策略为自动读取到指定的包尾
         */
		socketClient.getSocketPacketHelper().setReadStrategy(SocketPacketHelper.ReadStrategy.AutoReadToTrailer);
        
        /**
         * 根据连接双方协议设置的包尾数据
         * 每次接收数据包（包括心跳包）都会在检测接收到与包尾数据相同的byte[]时回调一个数据包
         *
         * 例：自动接收远程端所发送的socketClient.sendData(new byte[]{0x01, 0x02})【{0x01, 0x02}为将要接收的数据】的步骤为
         * 1. socketClient接收包头（如果设置了包头信息）（接收方式为一直读取到与包头相同的byte[],即可能过滤掉包头前的多余信息）
         * 2. socketClient接收正文和包尾（接收方式为一直读取到与尾相同的byte[]）
         * 3. socketClient回调数据包
         *
         * 使用{@link com.vilyever.socketclient.helper.SocketPacketHelper.ReadStrategy.AutoReadToTrailer}必须设置此项
         * 用于分隔多条消息
         */
		socketClient.getSocketPacketHelper().setReceiveTrailerData(new byte[]{0x13, 0x10});
	}

}