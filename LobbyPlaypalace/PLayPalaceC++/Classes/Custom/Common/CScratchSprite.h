#pragma once
#include "SlotGame/base/utils/CSpriteButton.h"
#include "Custom/Common/CustomRenderTexture.h"

class CScratchSprite : public CustomRenderTexture {
private:
	cocos2d::Vector<cocos2d::DrawNode*> brushes;
	cocos2d::Sprite* mask;
	GameSlot::CSpriteButton* spriteButton;
	std::function<void(float percent)> listener;

	int brushRadius = 40;

	void initScratch(cocos2d::Sprite* mask);

	void onTouchMove(cocos2d::Touch* touch);
	void onTouchEnd();

	void calculateProgress(float* percent);
public:
	static CScratchSprite* createScratchSprite(cocos2d::Sprite* mask);

	~CScratchSprite();

	void reset();

	void scratchAll();
	void scratchAllAndRunListener();

	void setEnabled(bool isEnabled);

	void setOnScratchListener(const std::function<void(float percent)>& listener) { this->listener = listener; }
};