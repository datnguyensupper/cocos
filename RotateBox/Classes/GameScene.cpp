#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "Helper.h"
#include "PopupController.h"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "PluginFacebook/PluginFacebook.h"
#endif

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	Label* label = Label::createWithSystemFont("Game Scene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
	this->addChild(label);
	label->setVisible(false);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(schedule_selector(GameScene::spawnEnemy), ENEMY_SPAWN_FREQUENCY );

	createWorldBounds();
	createPlayer();
	handleTouchController();
	soundController.PlayBackgroundMusic();
	soundController.CreateSoundControl(this);

	updateTextScore();

    return true;
}

void GameScene::updateTextScore() {

	UserDefault * def = UserDefault::getInstance();
	if (scoreText == nullptr &&
		maxScoreText == nullptr) {
		score = 0;
		maxScore = def->getIntegerForKey(CACHE_MAX_SCORE, 0);

		scoreText = LabelTTF::create("Score : 0", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
		scoreText->setHorizontalAlignment(TextHAlignment::RIGHT);
		scoreText->setAnchorPoint(Vec2(1, 1));
		scoreText->setPosition(Vec2(visibleSize.width - 20, visibleSize.height-20));
		this->addChild(scoreText,10);

		maxScoreText = LabelTTF::create("", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
		maxScoreText->setHorizontalAlignment(TextHAlignment::RIGHT);
		maxScoreText->setAnchorPoint(scoreText->getAnchorPoint());
		maxScoreText->setPosition(Vec2(scoreText->getPosition().x, scoreText->getPosition().y - scoreText->getContentSize().height));
		this->addChild(maxScoreText,10);
	}

	if (score > maxScore) {
		maxScore = score;
		def->setIntegerForKey(CACHE_MAX_SCORE, maxScore);
	}
	def->flush();


	__String * scoreStr = __String::createWithFormat("Score : %i", score);
	scoreText->setString(scoreStr->getCString());
	__String * maxScoreStr = __String::createWithFormat("Top Score : %i", maxScore);
	maxScoreText->setString(maxScoreStr->getCString());
}

void GameScene::handleTouchController() {

	// Add a "touch" event listener to our sprite
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool {
		GameScene * gameScene = static_cast<GameScene *>(event->getCurrentTarget());
		if (gameScene->isDied) {
			return false;
		}
		gameScene->lastTouchLocation = touch->getLocation();
		return true;
	};
	/*touchListener->onTouchEnded = [](Touch* touch, Event* event)->void {

	};*/
	touchListener->onTouchMoved = [](Touch* touch, Event* event)->void {
		GameScene * gameScene = static_cast<GameScene *>(event->getCurrentTarget());
		if (gameScene->isDied) {
			return;
		}

		Vec2 translate = touch->getLocation() - gameScene->lastTouchLocation;
		if (abs(translate.y) > abs(translate.x)) {
			if (gameScene->playerRed->getRotation() > 360 ||
				gameScene->playerRed->getRotation() < -360) {
				gameScene->playerRed->setRotation(0);
			}
			gameScene->playerRed->setRotation(gameScene->playerRed->getRotation() - translate.y);
		}
		else {
			Vec2 newPosition = Vec2(gameScene->playerRed->getPosition().x + translate.x, gameScene->playerRed->getPosition().y);
			if (newPosition.x < gameScene->playerRed->getContentSize().width) {
				newPosition.x = gameScene->playerRed->getContentSize().width;
			}
			else if (newPosition.x > gameScene->visibleSize.width-gameScene->playerRed->getContentSize().width) {
				newPosition.x = gameScene->visibleSize.width - gameScene->playerRed->getContentSize().width;
			}
			gameScene->playerRed->setPosition(newPosition);
			
		}
		//CCLOG("player red angle: %f",gameScene->playerRed->getRotation());
		gameScene->lastTouchLocation = touch->getLocation();
	};
	//touchListener->onTouchCancelled = [](Touch* touch, Event* event)->void {

	//};
	//   
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


}

void GameScene::spawnEnemy(float dt) {
	if (isDied) {
		// dont spawn enemy
		return ;
	}
	enemyController.SpawnEnemy(this, playerRed);
}

void GameScene::createWorldBounds() {

	auto background = Sprite::create("bg.jpg");
	background->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
	this->addChild(background);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);
	edgeBody->setDynamic(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	
	this->addChild(edgeNode);
}

void GameScene::createPlayer() {

	playerRed = Sprite::create("shield.png");
	playerRed->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	playerRed->setAnchorPoint(Vec2(0.5, 0));
	playerRed->setColor(Color3B::RED);
	//playerRed->setScaleX(2);
	auto playerBodyRed = PhysicsBody::createBox(Size(playerRed->getContentSize().width, playerRed->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBodyRed->setGravityEnable(false);
	playerBodyRed->setDynamic(false);
	playerBodyRed->setCollisionBitmask(PLAYER_COLLISION_BITMASK_RED);
	playerBodyRed->setContactTestBitmask(true);
	playerRed->setPhysicsBody(playerBodyRed);
	//playerRed->addComponent(playerBodyRed);

	playerBlue = Sprite::create("shield.png");
	playerBlue->setPosition(Vec2(0, -playerBlue->getContentSize().height));
	playerBlue->setAnchorPoint(Vec2(0, 1));
	playerBlue->setColor(Color3B::BLUE);
	playerBlue->setScaleY(-1);
	auto playerBodyBlue = PhysicsBody::createBox(Size(playerBlue->getContentSize().width, playerBlue->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//playerBodyBlue->setPositionOffset(Vec2(0, -player->getContentSize().height / 4));
	//set the body isn't affected by the physics world's gravitational force
	playerBodyBlue->setGravityEnable(false);
	playerBodyBlue->setDynamic(false);
	playerBodyBlue->setCollisionBitmask(PLAYER_COLLISION_BITMASK_BLUE);
	playerBodyBlue->setContactTestBitmask(true);
	playerBlue->setPhysicsBody(playerBodyBlue);
	//player->addComponent(playerBodyBlue);


	//player->setVisible(false);
	
	playerRed->addChild(playerBlue);
	this->addChild(playerRed);

}

bool GameScene::onContactBegin(cocos2d::PhysicsContact & contact) {

	if (isDied) {
		return false;
	}
	PhysicsBody * a = contact.getShapeA()->getBody();
	PhysicsBody * b = contact.getShapeB()->getBody();
	/*PhysicsBody * enemy = nullptr;
	PhysicsBody * player = nullptr;*/

	//cocos2d::log("a mask : %i; b mask : %i", a->getCollisionBitmask(),b->getCollisionBitmask());
	
	if (
		(ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_RED == b->getCollisionBitmask()) ||
		(ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_BLUE == b->getCollisionBitmask()) ||
		(a->getCollisionBitmask() == b->getCollisionBitmask())) {
		return false;
	}
	else if (
	    (PLAYER_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_BLUE == b->getCollisionBitmask()) ||
		(PLAYER_COLLISION_BITMASK_RED == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_RED == b->getCollisionBitmask()) ||

		(ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() &&
		PLAYER_COLLISION_BITMASK_BLUE == b->getCollisionBitmask()) ||
		(ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() &&
		PLAYER_COLLISION_BITMASK_RED == b->getCollisionBitmask())) {
		
		PhysicsBody * enemy = 
					(ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() ||
						ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask())?a:b;
		enemy->getNode()->removeFromParentAndCleanup(true);

		soundController.PlayCoinSound();
		score++;
		updateTextScore();

		return false;
	}
	else if (
		(PLAYER_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_RED == b->getCollisionBitmask()) ||
		(PLAYER_COLLISION_BITMASK_RED == a->getCollisionBitmask() &&
		ENEMY_COLLISION_BITMASK_BLUE == b->getCollisionBitmask()) ||

		(ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() &&
		PLAYER_COLLISION_BITMASK_BLUE == b->getCollisionBitmask()) ||
		(ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() &&
		PLAYER_COLLISION_BITMASK_RED == b->getCollisionBitmask())) {

		playerDied();

		return false;
	}
	return true;
}

void GameScene::onContactSeparate(cocos2d::PhysicsContact & contact) {

	PhysicsBody * a = contact.getShapeA()->getBody();
	PhysicsBody * b = contact.getShapeB()->getBody();

	if (ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask() ||
		ENEMY_COLLISION_BITMASK_BLUE == b->getCollisionBitmask() ||
		ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() ||
		ENEMY_COLLISION_BITMASK_RED == b->getCollisionBitmask()) {

		PhysicsBody * enemy = 
			(ENEMY_COLLISION_BITMASK_RED == a->getCollisionBitmask() ||
				ENEMY_COLLISION_BITMASK_BLUE == a->getCollisionBitmask())?a:b;

		//player->setVisible(false);
		// maintain speed up enemy 
		auto direction = Helper::getInstance()->normalizeDirection(enemy->getVelocity());
		enemy->setVelocity(Vec2(ENEMY_SPEED*visibleSize.width*direction.x, ENEMY_SPEED*visibleSize.height*direction.y));
	}

}

void GameScene::playerDied() {
	if (isDied) {
		return;
	}
	soundController.PlayLooseSound();
	cocos2d::log("player died");
	isDied = true;
	popupController.CreatePopupGameOver(this,score,maxScore);
}

void GameScene::restartGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	cocos2d::log("restart butotn click %i", touchType);
	if (touchType == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		static_cast<ui::Button *>(sender)->setScale(1.4);
	}
	else if (touchType == cocos2d::ui::Widget::TouchEventType::ENDED ||
		touchType == cocos2d::ui::Widget::TouchEventType::CANCELED) {
		static_cast<ui::Button *>(sender)->setScale(1.5);
	}
	if (touchType == cocos2d::ui::Widget::TouchEventType::ENDED) {
		static_cast<ui::Button *>(sender)->setTouchEnabled(false);
		this->scheduleOnce(schedule_selector(GameScene::GoToGameScene), 0);
	}
}

void GameScene::shareFacebook(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	cocos2d::log("restart butotn click %i", touchType);
	if (touchType == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		static_cast<ui::Button *>(sender)->setScale(1.4);
	}
	else if (touchType == cocos2d::ui::Widget::TouchEventType::ENDED ||
		touchType == cocos2d::ui::Widget::TouchEventType::CANCELED) {
		static_cast<ui::Button *>(sender)->setScale(1.3);
	}
	if (touchType == cocos2d::ui::Widget::TouchEventType::ENDED) {
		//static_cast<ui::Button *>(sender)->setTouchEnabled(false);
		static_cast<ui::Button *>(sender)->setScale(1.3);

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		/*if (!sdkbox::PluginFacebook::isLoggedIn()) {
			sdkbox::PluginFacebook::login();
		}*/
		__String * scoreStr = __String::createWithFormat("Congratulations! You beat your personal record! Your new score is %i", maxScore);
		sdkbox::FBShareInfo info;
		info.type = sdkbox::FB_LINK;
		info.link = "https://play.google.com/store/apps/details?id=com.donick.rotatebox";
		info.title = "Rotate Defense!";
		info.text = scoreStr->getCString();
		//info.image = "http://cocos2d-x.org/images/logo.png";
		sdkbox::PluginFacebook::dialog(info);
#endif

	}
}

void GameScene::GoToGameScene(float dt) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}