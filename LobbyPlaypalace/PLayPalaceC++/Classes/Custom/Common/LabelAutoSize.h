#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-20
* file: LabelAutoSize.h, LabelAutoSize.cpp
*/
#include "cocos2d.h"


#include "ui/CocosGUI.h"


USING_NS_CC;

enum LabelAutoFitType {
	Resize,
	TrimString
};
class ButtonScaleChild;
class LabelAutoSize : public cocos2d::Label {
private:
	cocos2d::Size _textArea = cocos2d::Size::ZERO;
	LabelAutoFitType autofitType;
    ButtonScaleChild * parentBtnScaleChild = nullptr;

	void resizeToFit(float minScale = 0, float maxScale = 1);
	void trimStringToFit();
public:
	LabelAutoSize(TextHAlignment hAlignment = TextHAlignment::LEFT,
		TextVAlignment vAlignment = TextVAlignment::TOP );

	static LabelAutoSize * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
		const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
		TextVAlignment vAlignment = TextVAlignment::TOP);

	static LabelAutoSize* createWithTTF(const TTFConfig& ttfConfig, const std::string& text,
		TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);
	/**
	* Allocates and initializes a Label, with a bitmap font file.
	*
	* @param bmfontPath A bitmap font file, it's a FNT format.
	* @param text The initial text.
	* @param hAlignment Text horizontal alignment.
	* @param maxLineWidth The max line width.
	* @param imageOffset
	*
	* @return An automatically released Label object.
	* @see setBMFontFilePath setMaxLineWidth
	*/
	static LabelAutoSize* createWithBMFont(const std::string& bmfontPath, const std::string& text,
		const TextHAlignment& hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0,
		const Vec2& imageOffset = Vec2::ZERO);

	virtual void setString(const std::string& text, float minScale, float maxScale);
	virtual void setString(const std::string& text) override;

    void setParentButtonScaleChild(ButtonScaleChild *btnScaleChild){
        parentBtnScaleChild = btnScaleChild;
    }
    
	void setTextAreaSize(cocos2d::Size areaSize) {
		this->_textArea = areaSize;
		this->setString(this->getString());
	}

	cocos2d::Size getTextAreaSize() {
		return this->_textArea;
	}

	void setAutoFitType(LabelAutoFitType autofitType) { this->autofitType = autofitType; }
};
