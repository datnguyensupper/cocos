#pragma once
#include "cocos2d.h"

class AnimationHelper
{
private:
	std::map<std::string, cocos2d::Vector<cocos2d::SpriteFrame*>> listAnimFrames;
public:
	/** Returns the shared instance of the AnimationHelper.
	* @return The instance of the AnimationHelper.
	*/
	static AnimationHelper* getInstance();
	/// <summary>
	/// create animaton by frame name
	/// </summary>
	/// <param name="plist"></param>
	/// <param name="frameFormat"></param>
	/// <param name="startFrame"></param>
	/// <param name="endFrame"></param>
	/// <param name="fps"></param>
	/// <param name="loopTimes"></param>
	/// <returns></returns>
	cocos2d::FiniteTimeAction* createAnimationByFrameName(
		const std::string& plist,
		const std::string& frameFormat,
		int startFrame,
		int endFrame,
		float fps,
		int loopTimes);
	/// <summary>
	/// create animation with list of file
	/// </summary>
	/// <param name="fileNameFormat">format of name of list file</param>
	/// <param name="startFrame"></param>
	/// <param name="endFrame"></param>
	/// <param name="fps"></param>
	/// <param name="loopTimes"></param>
	/// <returns></returns>
	cocos2d::FiniteTimeAction* createAnimationByFileName(
		const std::string& fileNameFormat,
		int startFrame,
		int endFrame,
		float fps,
		int loopTimes);
	/// <summary>
	/// create animation with file
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="animationName"></param>
	/// <param name="loopTimes"></param>
	/// <returns></returns>
	cocos2d::FiniteTimeAction* createAnimationWithFile(
		const std::string& fileName,
		const std::string& animationName,
		int loopTimes);

	void release();
};
