#include "HeaderMagicItemBtn.h"
#include "Constant/Defination.h"
#include "Helper/AnimationHelper.h"

USING_NS_CC;
using namespace std;

void HeaderMagicItemBtn::reset()
{
	this->additionSprite1->setVisible(false);
	this->animationSprite->setVisible(false);
	this->animationSprite->stopAllActions();
	this->animationSprite->setScale(1);
	this->animationSprite->setRotation(0);
}

void HeaderMagicItemBtn::setupPosForPinkBG()
{
	this->setPosition(Vec2(defaultPos.x - 15, defaultPos.y));
	this->getScaleNode()->setPosition(Vec2(_contentSize.width * 0.5f + 15, _contentSize.height * 0.5f));
}

void HeaderMagicItemBtn::setupPosForYellowBG()
{
	this->setPosition(defaultPos);
	this->getScaleNode()->setPosition(Vec2(_contentSize.width * 0.5f, _contentSize.height * 0.5f));
}

void HeaderMagicItemBtn::changeItemType(LobbyConstant::MagicItemType newItemType)
{
	if (defaultPos == Vec2::ZERO) {
		defaultPos = this->getPosition();
	}
	this->reset();
	switch (newItemType)
	{
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_YELLOW_BG,ui::Widget::TextureResType::PLIST);
		this->additionSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_100_BIG_WIN);
		this->animationSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_100_BIG_WIN_1);
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::create(
					DelayTime::create(0.5f),
					ScaleTo::create(1.0f, -1, 1),
					ScaleTo::create(1.0f, 1, 1),
					nullptr
				)
			)
		);
		this->animationSprite->setVisible(true);
		this->setupPosForYellowBG();
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_YELLOW_BG, ui::Widget::TextureResType::PLIST);
		this->additionSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN);
		this->animationSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN_1);
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::create(
					DelayTime::create(0.5f),
					ScaleTo::create(1.0f, -1, 1),
					ScaleTo::create(1.0f, 1, 1),
					nullptr
				)
			)
		);
		this->animationSprite->setVisible(true);
		this->setupPosForYellowBG();
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_PINK_BG,ui::Widget::TextureResType::PLIST);
		this->additionSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_10);
		this->animationSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_10_1);
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					DelayTime::create(0.5f),
					RotateBy::create(1.0f, 360)
				)
			)
		);
		this->animationSprite->setVisible(true);
		this->additionSprite1->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_10_2);
		this->additionSprite1->setVisible(true);
		this->setupPosForPinkBG();
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_PINK_BG,ui::Widget::TextureResType::PLIST);
		this->additionSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_20);
		this->animationSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_20_1);
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					DelayTime::create(0.5f),
					RotateBy::create(1.0f, 360)
				)
			)
		);
		this->animationSprite->setVisible(true);
		this->additionSprite1->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_20_2);
		this->additionSprite1->setVisible(true);
		this->setupPosForPinkBG();
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_DOUBLE_EXP:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_PINK_BG,ui::Widget::TextureResType::PLIST);
		this->animationSprite->initWithSpriteFrameName("magic_item_double_exp_anim0");
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					DelayTime::create(0.5f),
					AnimationHelper::getInstance()->createAnimationByFrameName(
						PLIST_MAGIC_ITEM, "magic_item_double_exp_anim%i", 0, 16, 18, 1
					)
				)
			)
		);
		this->animationSprite->setVisible(true);
		//this->animationSprite->runAction(AnimationHelper::c);
		this->setupPosForPinkBG();
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SYMBOL:
		this->loadTextureNormal(PNG_FRAME_MAGIC_ITEM_YELLOW_BG, ui::Widget::TextureResType::PLIST);
		this->additionSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL);
		this->animationSprite->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_1);
		this->animationSprite->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					DelayTime::create(0.5f),
					RotateBy::create(1.0f, 360)
				)
			)
		);
		this->animationSprite->setVisible(true);
		this->additionSprite1->initWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_2);
		this->additionSprite1->setVisible(true);
		this->setupPosForYellowBG();
		break;
	default:
		break;
	}
}

// on "init" you need to initialize your instance
bool HeaderMagicItemBtn::init()
{
	//////////////////////////////
	// 1. super init first
	if (!ui::Button::init())
	{
		return false;
	}

	this->additionSprite = Sprite::create();
	this->addScaleNode(this->additionSprite);

	this->animationSprite = Sprite::create();
	this->animationSprite->setPosition(this->additionSprite->getPosition());
	this->addScaleNode(this->animationSprite);

	this->additionSprite1 = Sprite::create();
	this->additionSprite1->setPosition(this->additionSprite->getPosition());
	this->addScaleNode(this->additionSprite1);

	return true;
}