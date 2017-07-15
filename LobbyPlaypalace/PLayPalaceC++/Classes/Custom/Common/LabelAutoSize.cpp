#include "LabelAutoSize.h"
#include "Util/UtilFunction.h"

USING_NS_CC;

LabelAutoSize::LabelAutoSize(
	TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
		TextVAlignment vAlignment /* = TextVAlignment::TOP */) : Label(hAlignment, vAlignment)
{
	this->autofitType = LabelAutoFitType::Resize;
}

LabelAutoSize* LabelAutoSize::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
	auto ret = new (std::nothrow) LabelAutoSize(hAlignment, vAlignment);

	if (ret && ret->initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

LabelAutoSize* LabelAutoSize::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, int maxLineWidth /* = 0 */)
{
	auto ret = new (std::nothrow) LabelAutoSize(hAlignment);

	if (ret && ret->initWithTTF(ttfConfig, text, hAlignment, maxLineWidth))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

LabelAutoSize* LabelAutoSize::createWithBMFont(const std::string& bmfontFilePath, const std::string& text, const TextHAlignment& hAlignment /* = TextHAlignment::LEFT */, int maxLineWidth /* = 0 */, const Vec2& imageOffset /* = Vec2::ZERO */)
{
	auto ret = new (std::nothrow) LabelAutoSize(hAlignment);

	if (ret && ret->setBMFontFilePath(bmfontFilePath, imageOffset))
	{
		ret->setMaxLineWidth(maxLineWidth);
		ret->setString(text);
		ret->autorelease();

		return ret;
	}

	delete ret;
	return nullptr;
}

void LabelAutoSize::setString(const std::string& text)
{
	Label::setString(text);

	switch (autofitType)
	{
	case Resize:
		this->resizeToFit();
		break;
	case TrimString:
		this->trimStringToFit();
		break;
	default:
		break;
	}
}

void LabelAutoSize::resizeToFit()
{
	this->setScale(1);
	this->updateContent();
	float scaleByWidth = this->getContentSize().width == 0 ? 0 : this->_textArea.width * 1.0f / this->getContentSize().width;
	float scaleByHeight = this->getContentSize().height == 0 ? 0 : this->_textArea.height * 1.0f / this->getContentSize().height;
	float scaleValue = 0;
	if (abs(scaleByWidth) <= abs(scaleByHeight)
		|| abs(scaleByHeight) == 0) {
		scaleValue = scaleByWidth;
	}
	else
	{
		scaleValue = scaleByHeight;
	}
	if (scaleValue != 0
		&& abs(scaleValue < 1)) {
		this->setScale(scaleValue);
	}
}

void LabelAutoSize::trimStringToFit()
{
	this->updateContent();
	if (this->_textArea.width == 0 || this->getContentSize().width <= this->_textArea.width) return;

	Label::setString(this->getString() + ".");
	auto dotWidth = this->getLetter(this->getStringLength() - 1)->getContentSize().width;

	//String content only - abstract 3 dot "..."
	auto stringContentSize = this->_textArea.width - dotWidth * 3;

	auto totalLength = 0.0f;
	int i = 0;
	int lastLength = 0;
	string rootString = this->getString();
	string contentDisplay;
	while (totalLength < stringContentSize) {
		char ch = rootString.at(i);
		contentDisplay += ch;
		Label::setString(contentDisplay);

		int currentLength = this->getStringLength();
		if (currentLength > lastLength) {
			auto letter = this->getLetter(currentLength - 1);
			totalLength = letter->getPositionX() + this->getLetter(currentLength - 1)->getContentSize().width;
			lastLength = currentLength;
		}

		++i;
	}
	Label::setString(this->getString() + "...");
}