package org.cocos2dx.cpp.chat;


import com.avos.avoscloud.im.v2.AVIMClient;
import com.avos.avoscloud.im.v2.AVIMConversation;
import com.avos.avoscloud.im.v2.AVIMMessage;
import com.avos.avoscloud.im.v2.AVIMMessageHandler;
import com.avos.avoscloud.im.v2.messages.AVIMTextMessage;
import com.tbu.androidtools.Debug;

public class CustomMessageHandler extends AVIMMessageHandler{
	   //接收到消息后的处理逻辑 
	   @Override
	   public void onMessage(AVIMMessage message,AVIMConversation conversation,AVIMClient client){
		  Debug.e("onMessage 收到一条消息");
	     if(message instanceof AVIMTextMessage){
	       
	     }
	   }

	   public void onMessageReceipt(AVIMMessage message,AVIMConversation conversation,AVIMClient client){
		   Debug.e("onMessageReceipt 收到一条消息");
	   }    
}
