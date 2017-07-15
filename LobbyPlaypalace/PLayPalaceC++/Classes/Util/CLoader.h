#pragma once

#include "cocos2d.h"
#include "PoolSystem.h"

using namespace std;

class CLoader: public PoolObject
{
private:
	int totalFiles;
	int currentFiles;

	bool bStop = false;

	bool bLoadMainThread;
	bool bLoadNextFile;

	vector<string> resources;

	function<void()> callbackComplete;
	function<void(float progress)> callbackFileLoaded;
	/// <summary>
	/// finish loading resources
	/// </summary>
	void completeLoading();
	/// <summary>
	/// load next file in queue
	/// </summary>
	void loadNextFile();
	/// <summary>
	/// load image
	/// </summary>
	/// <param name="image">image path</param>
	void _loadImage(const string& image);
	/// <summary>
	/// load atlas
	/// </summary>
	/// <param name="plist">atlas info</param>
	void _loadPlist(const string& plist);
	/// <summary>
	/// load sound
	/// </summary>
	/// <param name="sound"></param>
	void _loadSound(const string& sound);

	void onFileLoaded(bool isFromSound = false);

	void resetLoading();
public:
	/** Returns the shared instance of the CLoader.
	* @return The instance of the CLoader.
	*/
	static CLoader* getInstance();
	/*
	* Destructor
	*/
	~CLoader();
	/* 
	* Loading function
	* @param resources: vector string contains resources
	* @param callbackComplete (optional): callback after loaded all resources
	* @param callbackFileLoaded (optional): callback after loaded a single resource
	* @param bLoadMainThread is loading resource in mainthread or note
	*/
	void startLoadingResources(
		const vector<string>& resources,
		const function<void()>& callbackComplete,
		const function<void(float progress)>& callbackFileLoaded,
		bool bLoadMainThread = false);
	/// <summary>
	/// stop current loading resource
	/// </summary>
	void stop();
	/// <summary>
	/// stop all loading resource
	/// </summary>
	void stopAll();
	/// <summary>
	/// active loading resource
	/// </summary>
	void active() override;
	/// <summary>
	/// deactivate loading rs
	/// </summary>
	void deactive() override;
	/// <summary>
	/// check for load next file
	/// </summary>
	/// <param name="dt"></param>
	void update(float dt);
};
