#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: ButtonScaleChild.h, ButtonScaleChild.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#define SCALE_NODE_TAG 123
class ButtonScaleChild : public cocos2d::ui::Button {
private:
	cocos2d::Node* scaleNode;
protected:
	virtual void onPressStateChangedToNormal() override;
	virtual void onPressStateChangedToPressed() override;
	virtual void onSizeChanged() override;
public:

	static ButtonScaleChild* create();

	static ButtonScaleChild* create(
		const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL);

	ButtonScaleChild();

	/**
	* 2017-02-15: Kiet: add scale node
	*/
	void addScaleNode(cocos2d::Node* nodeEffectByZoomScale) {
		if (!this->getProtectedChildByTag(SCALE_NODE_TAG))
		{
			this->scaleNode->setTag(SCALE_NODE_TAG);
			this->scaleNode->setCascadeOpacityEnabled(true);
			this->addProtectedChild(this->scaleNode);
		}
		if (nodeEffectByZoomScale->getParent() != this) {
			this->scaleNode->addChild(nodeEffectByZoomScale);
		}
	}

	cocos2d::Node* getScaleNode() {
		return this->scaleNode;
	}
};
