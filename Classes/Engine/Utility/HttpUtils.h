#ifndef HttpUtils_h__
#define HttpUtils_h__
#include <string>
#include <functional>

#include "network/HttpRequest.h"
#include "network/HttpClient.h"

USING_NS_CC;


typedef std::function<void(bool isSuccess, std::string data)> NetworkRequestCallback;

class HttpUtils {
public:
	static void addRequestPost(std::string url, std::string data, NetworkRequestCallback callback) {
		network::HttpRequest* cRequest = new network::HttpRequest();
		cRequest->setUrl(url.c_str());
		cRequest->setRequestType(network::HttpRequest::Type::POST);
		cRequest->setRequestData(data.c_str(), data.size());
		cRequest->setResponseCallback(
			[callback](network::HttpClient* client, network::HttpResponse* response) {
			if (!response || !response->isSucceed() || response->getResponseCode() == 404)
			{
				callback(false, "");
			}
			else {
				std::vector<char> *buffer = response->getResponseData();
				std::string str = std::string(buffer->begin(), buffer->end());
				callback(true, str);
			}

		}
		);
		network::HttpClient::getInstance()->setTimeoutForConnect(15);
		network::HttpClient::getInstance()->setTimeoutForRead(15);
		network::HttpClient::getInstance()->send(cRequest);
		cRequest->release();
	}

	static void addRequestGet(std::string url, NetworkRequestCallback callback = nullptr) {
		network::HttpRequest* cRequest = new network::HttpRequest();
		cRequest->setUrl(url.c_str());
		cRequest->setRequestType(network::HttpRequest::Type::GET);
		if (callback != nullptr) {
			cRequest->setResponseCallback(
				[callback](network::HttpClient* client, network::HttpResponse* response) {
					if (!response || !response->isSucceed() || response->getResponseCode() == 404)
					{
						callback(false, "");
					}
					else {
						std::vector<char> *buffer = response->getResponseData();
						std::string str = std::string(buffer->begin(), buffer->end());
						callback(true, str);
					}

				}
			);
		}
		network::HttpClient::getInstance()->setTimeoutForConnect(15);
		network::HttpClient::getInstance()->setTimeoutForRead(15);
		network::HttpClient::getInstance()->send(cRequest);
		cRequest->release();
	}
};
#endif // HttpUtils
