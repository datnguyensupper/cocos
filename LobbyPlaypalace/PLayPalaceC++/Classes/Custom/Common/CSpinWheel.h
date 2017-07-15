#pragma once

#include "cocos2d.h"

class CSpinWheel : public cocos2d::Sprite{
private:
	std::map<float, float> mWheelInfo;
	int iLoops;
	float iDuration;

public:
	CSpinWheel();
	virtual ~CSpinWheel();

	void initWheelInfo(const std::vector<float>& aValues);

	void setLoops(int iLoops) { this->iLoops = iLoops; }
	void setDuration(float iDuration) { this->iDuration = iDuration; }
	/**
	* static function create a spin wheel
	* @param fileName: texture file's name
	* @param aValues: array values of wheel - it must be opposite from clock direciton
	* @param iLoops: loops
	* @param iDuration: duration
	*/
	static CSpinWheel* createSpinWheelWithFile(
		const std::string& fileName, 
		const std::vector<float>& aValues, 
		int iLoops = 2,
		float iDuration = 5.0f);
	/**
	* static function create a spin wheel
	* @param spriteName: sprite frame's name
	* @param aValues: array values of wheel
	* @param iLoops: loops
	* @param iDuration: duration
	*/
	static CSpinWheel* createSpinWheelWithSpriteFrameName(
		const std::string& spriteName, 
		const std::vector<float>& aValues, 
		int iLoops = 2,
		float iDuration = 5.0f);
	/**
	* call to spin the wheel
	* @param value: value of this spin
	* @param cb: callback after finishing spin
	*/
	void spin(float value, const std::function<void()>& cb = nullptr, cocos2d::FiniteTimeAction* actionSpin = nullptr);
	/**
	* get next rotation for value
	* @param value
	*/
	float getNextRotation(float value);
};