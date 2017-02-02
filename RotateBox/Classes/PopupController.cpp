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

void PopupController::CreatePopupGameOver(cocos2d::Layer * layer, int score, int maxScore) {
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

	__String * scoreStr = __String::createWithFormat("%i", score);
	auto scoreText = LabelTTF::create(scoreStr->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE*1.5);
	scoreText->setColor(Color3B::BLACK);
	scoreText->setHorizontalAlignment(TextHAlignment::RIGHT);
	scoreText->setAnchorPoint(Vec2(0, 0.5));
	scoreText->setPosition(Vec2(50, 65));
	popupGameOver->addChild(scoreText, 10);

	__String * maxScoreStr = __String::createWithFormat("%i", maxScore);
	auto maxScoreText = LabelTTF::create(maxScoreStr->getCString(), scoreText->getFontName(), scoreText->getFontSize());
	maxScoreText->setColor(scoreText->getColor());
	maxScoreText->setHorizontalAlignment(TextHAlignment::RIGHT);
	maxScoreText->setAnchorPoint(scoreText->getAnchorPoint());
	maxScoreText->setPosition(Vec2(scoreText->getPosition().x, -scoreText->getPosition().y+5));
	popupGameOver->addChild(maxScoreText, 10);

	// move all the sprite across 100 and up 50
	popupGameOver->setPosition(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y);

	layer->addChild(popupGameOver,100);
}