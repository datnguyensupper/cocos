#include "PopupController.h"
#include "Definitions.h"
//#include "Helper.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

PopupController::PopupController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void PopupController::CreatePopupGameOver(cocos2d::Layer * layer, int score, int maxScore) {
	CCLOG("show popup game over");
	score = 200;
	maxScore = 200;
	// layer
	auto popupGameOver = Layer::create();

	//create background
	auto bg = Sprite::create("sprites/gameover/middle.jpg");
	bg->setScale(1.5);
	popupGameOver->addChild(bg);

	auto playBtn = ui::Button::create("sprites/gameover/play-btn.png",
		"sprites/gameover/play-btn.png");
	playBtn->setAnchorPoint(Vec2(0.5, 0.5));
	playBtn->setScale(1.2);
	playBtn->setPosition(Vec2(-70, -bg->getContentSize().height / 1.5));
	playBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::restartGame, static_cast<GameScene *>(layer)));
	popupGameOver->addChild(playBtn);

	auto shareBtn = ui::Button::create("sprites/gameover/fbshare.png",
		"sprites/gameover/fbshare.png");
	shareBtn->setAnchorPoint(playBtn->getAnchorPoint());
	shareBtn->setScale(1.3);
	shareBtn->setPosition(Vec2(-playBtn->getPosition().x, playBtn->getPosition().y));
	shareBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::shareFacebook, static_cast<GameScene *>(layer)));
	popupGameOver->addChild(shareBtn);

	auto title = Sprite::create("sprites/gameover/gameOver.png");
	title->setScale(1.3);
	title->setPosition(0, -playBtn->getPosition().y+30);
	popupGameOver->addChild(title);

	__String * scoreStr = __String::createWithFormat("%i", score);
	//auto scoreText = LabelTTF::create(scoreStr->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE*1.5);
	auto scoreText = CCLabelBMFont::create(scoreStr->getCString(), "fonts/bitmapFonts/carrier_command.xml");
	scoreText->setScale(0.7);
	scoreText->setColor(Color3B::BLACK);
	scoreText->setAlignment(cocos2d::CCTextAlignment::RIGHT);
	//scoreText->setHorizontalAlignment(TextHAlignment::RIGHT);
	scoreText->setAnchorPoint(Vec2(0, 0.5));
	scoreText->setPosition(Vec2(40, 34));
	popupGameOver->addChild(scoreText, 10);

	__String * maxScoreStr = __String::createWithFormat("%i", maxScore);
	/*auto maxScoreText = LabelTTF::create(maxScoreStr->getCString(), scoreText->getFontName(), scoreText->getFontSize());*/
	auto maxScoreText = CCLabelBMFont::create(maxScoreStr->getCString(), "fonts/bitmapFonts/carrier_command.xml");
	maxScoreText->setScale(scoreText->getScale());
	maxScoreText->setColor(Color3B::BLACK);
	maxScoreText->setAlignment(TextHAlignment::RIGHT);
	maxScoreText->setAnchorPoint(scoreText->getAnchorPoint());
	maxScoreText->setPosition(Vec2(scoreText->getPosition().x, -scoreText->getPosition().y+5));
	popupGameOver->addChild(maxScoreText, 10);

	// move all the sprite across 100 and up 50
	popupGameOver->setPosition(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y);

	layer->addChild(popupGameOver,100);
}