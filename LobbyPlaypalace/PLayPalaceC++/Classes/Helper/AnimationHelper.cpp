#include "AnimationHelper.h"
#include "Constant/Defination.h"

USING_NS_CC;

static AnimationHelper *_sharedAnimationHelper = nullptr;
AnimationHelper * AnimationHelper::getInstance()
{
	if (!_sharedAnimationHelper)
	{
		_sharedAnimationHelper = new (std::nothrow) AnimationHelper();
	}
	return _sharedAnimationHelper;
}
FiniteTimeAction * AnimationHelper::createAnimationByFrameName(
	const std::string& plist,
	const std::string& frameFormat,
	int startFrame,
	int endFrame,
	float fps,
	int loopTimes)
{
	std::string cacheName = frameFormat + "_" + ToString(startFrame) + "_" + ToString(endFrame);

	if (this->listAnimFrames.find(cacheName) == this->listAnimFrames.end()) {
		if (!SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(frameFormat.c_str(), startFrame))) {
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
		}
		Vector<SpriteFrame*> animFrames(endFrame - startFrame + 1);
		for (int i = startFrame; i <= endFrame; i++) {
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(frameFormat.c_str(), i));
			if (frame) {
				animFrames.pushBack(frame);
			}
		}
		this->listAnimFrames[cacheName] = animFrames;
	}
	//create a animation with the spriteframe array along with a period time
	auto animation = Animation::createWithSpriteFrames(this->listAnimFrames[cacheName], 1.0/ fps);
	
	//wrap the animate action with a repeat forever action
	FiniteTimeAction* action = nullptr;
	if (loopTimes == -1) {
		action = RepeatForever::create(Animate::create(animation));
	}
	else {
		animation->setLoops(loopTimes);
		action = Animate::create(animation);
	}
	return action;
}

cocos2d::FiniteTimeAction * AnimationHelper::createAnimationByFileName(
	const std::string& fileNameFormat,
	int startFrame,
	int endFrame,
	float fps,
	int loopTimes)
{
	auto animation = Animation::create();
	for (int i = startFrame; i <= endFrame; i++) {
		animation->addSpriteFrameWithFile(StringUtils::format(fileNameFormat.c_str(), i));
	}
	animation->setDelayPerUnit(1.0f / fps);
	//wrap the animate action with a repeat forever action
	FiniteTimeAction* action = nullptr;
	if (loopTimes == -1) {
		action = RepeatForever::create(Animate::create(animation));
	}
	else {
		animation->setLoops(loopTimes);
		action = Animate::create(animation);
	}
	return action;
}

FiniteTimeAction * AnimationHelper::createAnimationWithFile(
	const std::string& fileName,
	const std::string& animationName,
	int loopTimes)
{
	auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile(fileName);
	auto animation = cache->getAnimation(animationName);

	if (!animation) return nullptr;

	//wrap the animate action with a repeat forever action
	FiniteTimeAction* action = nullptr;
	if (loopTimes == -1) {
		action = RepeatForever::create(Animate::create(animation));
	}
	else {
		animation->setLoops(loopTimes);
		action = Animate::create(animation);
	}
	return action;
}

void AnimationHelper::release()
{
	listAnimFrames.clear();
	CC_SAFE_DELETE(_sharedAnimationHelper);
}
