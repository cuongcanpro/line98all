#pragma once
#ifndef HttpRequestHandler_h__
#define HttpRequestHandler_h__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

using namespace cocos2d;
using namespace cocos2d::network;
class HttpRequestHandler : public cocos2d::Ref
{
public:
	HttpRequestHandler(void);
	~HttpRequestHandler(void);

	void onCompleteGetVersion(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
    void onCompleteGetFake(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
	void onCompleteGetPackage(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);;
	void onCompleteGetIP(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
	void onCompleteGetIP2(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
	void onCompleteGetIP3(cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response);
};
#endif // HttpRequestHandler_h__

