#include "Helper4Sprite.h"

USING_NS_CC;


void Helper4Sprite::setBlendModeAdd(cocos2d::Sprite * sprite) {
	sprite->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
}


void Helper4Sprite::setColor4RangeOfLabel(cocos2d::Label * label, int from, int to, cocos2d::Color3B color) {
	for (int i = from; i <= to; i++) {
		if (label->getLetter(i) == nullptr) continue;
		Sprite *charSprite = (Sprite *)label->getLetter(i);
		charSprite->setColor(color);

	}
}


void Helper4Sprite::labelAppendString(cocos2d::Label * label, std::string appendString, cocos2d::Color3B color) {
	std::string oldString = label->getString();
	int fromPosition = oldString.length();
	int toPosition = oldString.length() + appendString.length() - 1;
	label->setString(oldString + appendString);
	setColor4RangeOfLabel(label, fromPosition, toPosition, color);
}


void Helper4Sprite::addOptimizeImageAsync(const std::string &filepath, const std::function<void(cocos2d::Texture2D*)>& callback) {
	TextureCache::getInstance()->addImageAsync(filepath,callback);
}

cocos2d::Texture2D* Helper4Sprite::getTextureFromSpriteFramename(const std::string& filename){
	cocos2d::SpriteFrameCache * spriteFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	cocos2d::SpriteFrame * spriteFrame = spriteFrameCache->getSpriteFrameByName(filename);
	return spriteFrame->getTexture();
}

Sprite* Helper4Sprite::createWithSpriteFrameName(const std::string& filename) {
	return Sprite::createWithSpriteFrameName(filename);
}


Sprite* Helper4Sprite::createOptimizeSprite(const std::string& filename) {
	return Sprite::create(filename);
}

Sprite* Helper4Sprite::createOptimizeSprite(const std::string& filename, const Rect& rect) {
	return Sprite::create(filename,rect);
}

Sprite* Helper4Sprite::createOptimizeSprite() {
	return Sprite::create();
}