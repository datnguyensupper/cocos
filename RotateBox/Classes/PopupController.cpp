#include "PopupController.h"
#include "Definitions.h"
#include "Helper.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

PopupController::PopupController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void PopupController::CreatePopupGameOver(cocos2d::Layer * layer) {
	CCLOG("show popup game over");

	// layer
	auto popupGameOver = Layer::create();

	//create background
	auto bg = Sprite::create("gameover/middle.jpg");
	bg->setScale(1.5);
	popupGameOver->addChild(bg);

	auto playBtn = ui::Button::create("gameover/play-btn.png",
		"gameover/play-btn.png");
	playBtn->setScale(1.5);
	playBtn->setPosition(Vec2(0, -bg->getContentSize().height / 1.5));
	playBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::restartGame, static_cast<GameScene *>(layer)));
	popupGameOver->addChild(playBtn);

	auto title = Sprite::create("gameover/gameOver.png");
	title->setScale(1.3);
	title->setPosition(0, -playBtn->getPosition().y + 50);
	popupGameOver->addChild(title);

	// move all the sprite across 100 and up 50
	popupGameOver->setPosition(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y);

	layer->addChild(popupGameOver,100);
}