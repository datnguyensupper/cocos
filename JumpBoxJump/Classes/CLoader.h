#pragma once

#include "cocos2d.h"
#include "PoolSystem.h"

using namespace std;

class CLoader: public PoolObject
{
private:
	int totalFiles;
	int currentFiles;

	vector<string> resources;

	function<void()> callbackComplete;
	function<void(float progress)> callbackFileLoaded;

	void completeLoading();

	void loadNextFile();

	void _loadImage(const string& image);
	void _loadPlist(const string& plist);
	void _loadSound(const string& sound);

	void onFileLoaded();

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
	*/
	void startLoadingResources(
		const vector<string>& resources,
		const function<void()>& callbackComplete,
		const function<void(float progress)>& callbackFileLoaded);

	void active() override;
};
