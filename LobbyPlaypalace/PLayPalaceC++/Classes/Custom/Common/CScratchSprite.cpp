#include "CScratchSprite.h"
#include "Constant/Defination.h"

USING_NS_CC;

void CScratchSprite::initScratch(cocos2d::Sprite* mask)
{
	this->setCascadeOpacityEnabled(true);
	this->mask = mask;

	this->spriteButton = GameSlot::CSpriteButton::createInvisibleButton(Rect(-Vec2(mask->getContentSize() / 2), mask->getContentSize()), nullptr, CC_CALLBACK_0(CScratchSprite::onTouchEnd, this));
	this->spriteButton->setCallOnUpWithoutCheck(true);
	this->spriteButton->setOnTouchMove(CC_CALLBACK_1(CScratchSprite::onTouchMove, this));
	this->addChild(this->spriteButton);

	this->mask->setPosition(this->mask->getContentSize() / 2);
	this->mask->retain();

	this->reset();
}

void CScratchSprite::onTouchMove(cocos2d::Touch * touch)
{
	Point start = Vec2(this->mask->getContentSize() / 2) + this->convertToNodeSpace(touch->getLocation());
	Point end = Vec2(this->mask->getContentSize() / 2) + this->convertToNodeSpace(touch->getPreviousLocation());

	this->begin();

	float distance = start.getDistance(end);

	if (distance > 1)
	{
		int d = (int)distance;
		for (int i = brushes.size(); i < d; ++i)
		{
			auto brush = DrawNode::create();
			brush->drawSolidCircle(Vec2::ZERO, this->brushRadius, 0, 64, Color4F(255, 255, 255, 255));
			brush->setBlendFunc({ GL_ZERO,GL_ZERO });
			brush->retain();
			brushes.pushBack(brush);
		}
		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			auto pos = Vec2(start.x + (difx * delta), start.y + (dify * delta));

			brushes.at(i)->setPosition(pos);
			brushes.at(i)->visit();
		}
	}

	this->end();
}

void CScratchSprite::onTouchEnd()
{
	auto percent = 0.0f;
	this->calculateProgress(&percent);
	if (this->listener) {
		this->listener(percent);
	}
	if (percent == 100) {
		this->spriteButton->setTouchEnabled(false);
	}
}

void CScratchSprite::calculateProgress(float* percent)
{
	auto img = this->newImage(false);

	auto imgPixelData = img->getData();
	auto len = img->getDataLen();

	auto totalRevealed = 0;

	for (int i = 0; i < img->getWidth(); i++)
	{
		for (int j = 0; j < img->getHeight(); j++)
		{

			unsigned char *pixel = imgPixelData + (i + j * img->getWidth()) * 4;

			GLubyte alpha = *(pixel + 3);

			if (alpha == 0) {
				totalRevealed++;
			}
		}
	}

	*percent = ceil(min(1.0f, totalRevealed * 4.0f / len) * 100);
	CC_SAFE_DELETE(img);
}

CScratchSprite * CScratchSprite::createScratchSprite(cocos2d::Sprite * mask)
{
	auto scratchSprite = new CScratchSprite();
	if (scratchSprite && scratchSprite->initWithWidthAndHeight(
		ceil(mask->getContentSize().width),
		ceil(mask->getContentSize().height), Texture2D::PixelFormat::RGBA8888, 0))
	{
		scratchSprite->autorelease();
		scratchSprite->initScratch(mask);
		return scratchSprite;
	}

	CC_SAFE_DELETE(scratchSprite);
	return NULL;
}

CScratchSprite::~CScratchSprite()
{
	CC_SAFE_RELEASE_NULL(mask);
	for (auto brush : brushes) {
		CC_SAFE_RELEASE_NULL(brush);
	}
	brushes.clear();
}

void CScratchSprite::reset()
{
	this->setEnabled(true);
	this->beginWithClear(0, 0, 0, 0);
	this->mask->visit();
	this->end();
}

void CScratchSprite::scratchAll()
{
	this->setEnabled(false);
	this->beginWithClear(0, 0, 0, 0);
	this->end();
}

void CScratchSprite::scratchAllAndRunListener()
{
	this->scratchAll();
	if (this->listener) {
		this->listener(100);
	}
}

void CScratchSprite::setEnabled(bool isEnabled)
{
	this->spriteButton->setTouchEnabled(isEnabled);
}
