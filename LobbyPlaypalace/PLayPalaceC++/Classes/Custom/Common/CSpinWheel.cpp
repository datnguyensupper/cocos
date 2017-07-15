#include "CSpinWheel.h"

USING_NS_CC;
CSpinWheel::CSpinWheel():
	iLoops(0),
	iDuration(0)
{
}
CSpinWheel::~CSpinWheel()
{
}
CSpinWheel * CSpinWheel::createSpinWheelWithFile(const std::string & fileName,
	const std::vector<float>& aValues,
	int iLoops,
	float iDuration)
{
	CSpinWheel* pSprite = new CSpinWheel();

	if (pSprite->initWithFile(fileName))
	{
		pSprite->autorelease();

		pSprite->iLoops = iLoops;
		pSprite->iDuration = iDuration;

		pSprite->initWheelInfo(aValues);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}
CSpinWheel * CSpinWheel::createSpinWheelWithSpriteFrameName(const std::string & spriteName,
	const std::vector<float>& aValues,
	int iLoops,
	float iDuration)
{
	CSpinWheel* pSprite = new CSpinWheel();

	if (pSprite->initWithSpriteFrameName(spriteName))
	{
		pSprite->autorelease();

		pSprite->iLoops = iLoops;
		pSprite->iDuration = iDuration;

		pSprite->initWheelInfo(aValues);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}
void CSpinWheel::spin(float value, const std::function<void()>& cb, cocos2d::FiniteTimeAction* actionSpin)
{

	actionSpin = actionSpin == nullptr ? EaseCubicActionOut::create(RotateBy::create(this->iDuration, this->getNextRotation(value))) : actionSpin;

	this->runAction(Sequence::createWithTwoActions(
		actionSpin,
		CallFunc::create(cb)
		));
}
float CSpinWheel::getNextRotation(float value)
{
	this->setRotation(fmodf(this->getRotation(), 360));

	float angle = this->mWheelInfo[value] - this->getRotation();
	angle += iLoops * 360;

	return angle;
}
void CSpinWheel::initWheelInfo(const std::vector<float>& aValues)
{
	this->mWheelInfo.clear();
	auto size = aValues.size();
	if (size == 0) {
		return;
	}
	auto element = 360.0f / size;
	for (int i = 0; i < size; i++) {
		this->mWheelInfo.insert(std::pair<float, float>(aValues[i], i * element));
	}
}