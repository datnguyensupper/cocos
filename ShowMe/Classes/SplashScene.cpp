#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "Controller4Score.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseScene::init() ) return false;

	Controller4Score::getInstance()->updateMaxScore();

    
#if IS_DEBUG
	auto label = Label::createWithSystemFont("Splash Scene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//	this->addChild(label);
#endif
    
    auto bg = Sprite::create("bg_flash.png");
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(bg);
    
    
	auto labelScore = LabelTTF::create("Score : " + std::to_string(Controller4Score::getInstance()->getCurrentScore())+"m", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
	labelScore->setAnchorPoint(Vec2(0.5, 0.5));
	labelScore->setVerticalAlignment(TextVAlignment::CENTER);
	labelScore->setHorizontalAlignment(TextHAlignment::CENTER);
	labelScore->setPosition(Vec2(visibleSize.width / 2-0, visibleSize.height / 2 + 50));
	this->addChild(labelScore);

	auto labelHighScore = LabelTTF::create("Max Score : " + std::to_string(Controller4Score::getInstance()->getMaxScore())+"m", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
	labelHighScore->setColor(Color3B::YELLOW);
	labelHighScore->setAnchorPoint(labelScore->getAnchorPoint());
	labelHighScore->setVerticalAlignment(labelScore->getVerticalAlignment());
	labelHighScore->setHorizontalAlignment(labelScore->getHorizontalAlignment());
	labelHighScore->setPosition(labelScore->getPosition() - Vec2(0, 60));
	this->addChild(labelHighScore);
	
	auto playBtn = ui::Button::create("play.png");
	playBtn->setPosition(Vec2(visibleSize.width/2-20, labelHighScore->getPosition().y-140));
	playBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED) return;
		scheduleOnce(schedule_selector(SplashScene::Go2LevelOneScene), DISPLAY_TIME_SPLASH_SCREEN);
	});
	addChild(playBtn);


	tutorialBtn = ui::Button::create("question.png", "question_clicked.png");
	//tutorialBtn->setScale(0.05);
	tutorialBtn->setPosition(Vec2(190+ visibleSize.width/2,85+ visibleSize.height/2));
	tutorialBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED) return;
        tutorialV->setVisible(!tutorialV->isVisible());
        
	});
	addChild(tutorialBtn);

	createTutorialView();

    return true;
}


void SplashScene::createTutorialView() {

	tutorialV = Node::create();
	tutorialV->setPosition(tutorialBtn->getPosition() + Vec2(50, 0));
	addChild(tutorialV);

	auto tutorialText = CCLabelBMFont::create("Swipe to create\n\n correct way!", "fonts/bitmapFonts/carrier_command.xml");
	tutorialText->setScale(0.5);
	tutorialText->setColor(Color3B::WHITE);
	tutorialText->setAlignment(TextHAlignment::LEFT);
	tutorialText->setAnchorPoint(Vec2(0, 0.5));
	tutorialV->addChild(tutorialText);
    
    Sprite * hand = Sprite::create("hand-touch.png");
    tutorialV->addChild(hand);
    hand->setPosition(Vec2(50,-70));
    
    Sequence * handAction = Sequence::create(MoveTo::create(1.0, Vec2(150,-70)),MoveTo::create(0, Vec2(50,-70)),nullptr);
    RepeatForever * handActionRepeat = RepeatForever::create(handAction);
    hand->runAction(handActionRepeat);
    tutorialV->setVisible(false);
            
}


