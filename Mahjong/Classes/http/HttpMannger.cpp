#include "HttpMannger.h"

HttpMannger* HttpMannger::_instance = NULL;

HttpMannger::HttpMannger(){
    this->init();
}

void HttpMannger::init(){
}

HttpMannger* HttpMannger::getInstance(){
    if(_instance == NULL){
		_instance = new HttpMannger();
    }
    return _instance;
}

void HttpMannger::httpToPostRequestToGetUrlImg(std::string url)
{
	HttpClientUtill::getInstance()->onGetHttp(url.c_str(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForGetUrlImg, this));
}

void HttpMannger::onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response)
{
	std::vector<char> *buffer;
	while (1)
	{
		if (!response)
		{
			return;
		}
		if (!response->isSucceed())
		{
			return;
		}
		long statusCode = response->getResponseCode();

		buffer = response->getResponseData();
		break;
	}

	EventCustom event(response->getHttpRequest()->getUrl());
	event.setUserData(buffer);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

}

void HttpMannger::httpToPostRequestToSendImage(std::string url,std::string postData){

    HttpClientUtill::getInstance()->onPostHttp(postData.c_str(), url.c_str(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForSendImage, this));
}

void HttpMannger::onHttpRequestCompletedForSendImage(HttpClient *sender, HttpResponse *response){
//    std::vector<char> *buffer;
//    while (1)
//    {
//        if (!response)
//        {
//            return;
//        }
//        if (!response->isSucceed())
//        {
//            return;
//        }
//        long statusCode = response->getResponseCode();
//        log("KKKKKKKKKKKK = %d",(int)statusCode);
//        buffer = response->getResponseData();
//        break;
//    }
    long statusCode = response->getResponseCode();
    log("KKKKKKKKKKKK = %d",(int)statusCode);
}