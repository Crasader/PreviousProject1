//
//  ImagePicker.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/15.
//
//

#ifndef ImagePicker_hpp
#define ImagePicker_hpp

// CC_PLATFORM_ANDROID
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

/**
 * 图像选择器
 */
class ImagePicker
{
public:
    // 获取选择器单例
    static ImagePicker* getInstance();
    // 销毁
    static void destoryInstance();
public:
    // 显示本地相册与相机选择器
    void callImagePickerWithPhotoAndCamera(const std::function<void(std::string)>& callback);
    
    // 设置监听
    void setListener(const std::function<void(std::string)>& callback);
    
    // 移除监听
    void removeListener();
    
    // 打开相册
    void openPhoto();
    
    // 打开相机
    void openCamera();
    
    // CC_PLATFORM_IOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // 设置AppController
    void setViewController(void* viewController);
#endif
    
protected:
    // 初始化
    bool init();
    
    ImagePicker();
    
    std::function<void(std::string)> m_callback;
    
    static ImagePicker* s_instance;
    
    // CC_PLATFORM_IOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void* m_viewController;
#endif
    
};

#endif /* ImagePicker_hpp */
