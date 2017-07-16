#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-13
* file: DownloadImageManager.h.h, DownloadImageManager.h.cpp
*/
#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "json/writer.h"
#include "json/document.h"

using namespace rapidjson;

class DownloadImageManager
{
private:
	std::map<std::string, std::vector<std::function<void(cocos2d::Texture2D* texture)>>> downloadingImageWithCallback;
	std::vector<std::string> downloadImageQueue;
	std::map<std::string, std::string> redirectMap;
	static DownloadImageManager* s_instance;

	/**
	* 2017-02-06: Kiet: method called after load image from url completed
	*/
	void onHttpRequestLoadImageCompleted(
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response
	);

	cocos2d::Image * currentImage;
	/// <summary>
	/// call back 4 receive circle image
	/// </summary>
    /// <param name="url">url of image data</param>
    /// <param name="response">HTTP Response</param>
	void onReceivedCircleImage(
		const std::string &url,
        cocos2d::network::HttpResponse* response
	);
	/// <summary>
	/// download image with url
	/// </summary>
	/// <param name="url"></param>
	void downloadImage(
		const std::string &url);
	/// <summary>
	/// add download url to queue and start download
	/// </summary>
	/// <param name="url"></param>
	/// <param name="callback"></param>
	void addDownloadToQueueAndCheckDownload(
		const std::string &url,
		std::function<void(cocos2d::Texture2D* texture)> callback
	);
	/// <summary>
	/// down load next file in queue
	/// </summary>
	void checkAndDownload();
public:
	/**
	* 2017-03-13: Kiet: get instance class
	*/
	static DownloadImageManager* getInstance();
#pragma region Download Files
	/**
	* 2017-02-21: Kiet: check image in cache then call callback to return texture with url as key correspond
	* if texture not exist in cache, will download image from url and store it in cache with key is url
	*/
	void loadImageFromCacheOrDownload(const std::string &url, std::function<void(cocos2d::Texture2D* texture)> callback);
#pragma endregion
};
