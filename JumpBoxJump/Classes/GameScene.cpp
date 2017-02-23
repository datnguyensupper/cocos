#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "Helper4Array.h"

#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#endif

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -SQUARE_GRAVITY));
	
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void GameScene::createGameLevels() {
	
	//std::vector<std::vector<Barrier>> gameLevelsRandom;
	std::vector<Barrier> level;
	Barrier barrier;

	//floor 0
	barrier= { 60,30,200 };
	level.push_back(barrier);
	barrier = {60,30,400};
	level.push_back(barrier);
	barrier = {60,30,600};
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 1
	level = std::vector<Barrier>();
	barrier = { 70,25,350 };
	level.push_back(barrier);
	barrier = { 30,20,100 };
	level.push_back(barrier);
	barrier = { 40,30,700 };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 2
	level = std::vector<Barrier>();
	barrier = { 10,35,150 };
	level.push_back(barrier);
	barrier = { 10,35,400 };
	level.push_back(barrier);
	barrier = { 10,35,650 };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 3
	level = std::vector<Barrier>();
	barrier = { 80,10,280 };
	level.push_back(barrier);
	barrier = { 80,10,480 };
	level.push_back(barrier);
	barrier = { 80,10,960 };
	level.push_back(barrier);
	barrier = { 80,10,1160 };
	level.push_back(barrier);
	barrier = { 80,10,1440 };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 4
	level = std::vector<Barrier>();
	barrier = { 10,10,100 };
	level.push_back(barrier);
	barrier = { 10,10,200 };
	level.push_back(barrier);
	barrier = { 10,10,300 };
	level.push_back(barrier);
	barrier = { 10,10,400 };
	level.push_back(barrier);
	barrier = { 10,10,500 };
	level.push_back(barrier);
	barrier = { 10,10,600 };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 5
	level = std::vector<Barrier>();
	barrier = { 10,40,200 };
	level.push_back(barrier);
	barrier = { 10,40,400 };
	level.push_back(barrier);
	barrier = { 10,40,600 };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	gameLevels.push_back(gameLevelsRandom[0]);
	gameLevels.push_back(gameLevelsRandom[1]);
	gameLevels.push_back(gameLevelsRandom[2]);
	gameLevels.push_back(gameLevelsRandom[3]);


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

	theSquare = nullptr;

	floorY = {112-EXTRA_HEIGHT,224 - EXTRA_HEIGHT,336 - EXTRA_HEIGHT,448 - EXTRA_HEIGHT };
	levelColors = {Color3B::Color3B(232,29,98),Color3B::Color3B(155,38,175),Color3B::Color3B(32,149,242), Color3B::Color3B(75,174,79),Color3B::Color3B(254,234,58),Color3B::Color3B(121,85,72),Color3B::Color3B(95,124,138), };

	createGameLevels();
	updateTextScore();
	createTheSquare();
	createLevels();
	createWorldBounds();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(GameScene::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameScene::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Add a "touch" event listener to our sprite
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* event)->bool {
		squareJump();
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

void GameScene::updateTextScore() {

	UserDefault * def = UserDefault::getInstance();
	if (scoreText == nullptr &&
		maxScoreText == nullptr) {
		score = 0;
		maxScore = def->getIntegerForKey(CACHE_MAX_SCORE, 0);

		/*scoreText = LabelTTF::create("Score : 0", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);*/
		scoreText = CCLabelBMFont::create("Score : 0", "fonts/bitmapFonts/carrier_command.xml");
		scoreText->setScale(0.5);
		scoreText->setAlignment(TextHAlignment::RIGHT);
		scoreText->setAnchorPoint(Vec2(1, 1));
		scoreText->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 10));
		this->addChild(scoreText, 10);

	/*	maxScoreText = LabelTTF::create("", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);*/
		maxScoreText = CCLabelBMFont::create("Score : 0", "fonts/bitmapFonts/carrier_command.xml");
		maxScoreText->setScale(scoreText->getScale());
		maxScoreText->setAlignment(TextHAlignment::RIGHT);
		maxScoreText->setAnchorPoint(scoreText->getAnchorPoint());
		maxScoreText->setPosition(Vec2(scoreText->getPosition().x, scoreText->getPosition().y - scoreText->getContentSize().height));
		this->addChild(maxScoreText, 10);
	}

	if (score > maxScore) {
		maxScore = score;
		def->setIntegerForKey(CACHE_MAX_SCORE, maxScore);
		def->flush();
	}


	__String * scoreStr = __String::createWithFormat("Score : %i", score);
	scoreText->setString(scoreStr->getCString());
	__String * maxScoreStr = __String::createWithFormat("Top Score : %i", maxScore);
	maxScoreText->setString(maxScoreStr->getCString());
}

void GameScene::createTheSquare() {

	if (theSquare == nullptr) {

		theSquare = Sprite::create("sprites/pattern4.png");
		//theSquare->setColor(Color3B::Color3B(255, 0, 255));
		theSquare->setAnchorPoint(Vec2(0.5, 0.5));
		theSquare->setContentSize(Size(SQUARE_SIZE, SQUARE_SIZE));
		this->addChild(theSquare,2);
		//playerRed->setScaleX(2);


	}
	else {
		theSquare->getPhysicsBody()->removeFromWorld();
	}
	theSquare->setRotation(0);
	this->scheduleOnce(schedule_selector(GameScene::resetSquarePosition), 0);
}

void GameScene::resetSquarePosition(float dt) {

	Vec2 squarePosition = Vec2((levelFloor % 2 == 0) ? floorX + 20 : floorX + FLOOR_WIDTH - 20,
			visibleSize.height - (floorY[levelFloor] - SQUARE_SIZE / 2));
	theSquare->setPosition(squarePosition);

	auto playerBody = PhysicsBody::createBox(Size(theSquare->getContentSize().width, theSquare->getContentSize().height),
		PhysicsMaterial(/*density*/0.0f, /*restitution*/0.0f,/*friction*/ 0.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBody->setGravityEnable(true);
	//playerBody->setGravityEnable(false);
	//playerBody->setDynamic(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK_PLAY);
	playerBody->setContactTestBitmask(true);
	//playerBody->applyForce(Vec2(SQUARE_SPEED, 0));

	playerBody->setVelocity(Vec2((levelFloor % 2 == 0) ? SQUARE_SPEED : -SQUARE_SPEED, 0));
	playerBody->setVelocityLimit(450);
	playerBody->setRotationEnable(false);


	theSquare->setPhysicsBody(playerBody);
}

void GameScene::squareJump() {

	if (isDead) {
		return;
	}

	if (canJump) {

		canJump = false;
		PhysicsBody * playerBody = theSquare->getPhysicsBody();
		if (playerBody != nullptr) {
		/*	playerBody->setVelocity(Vec2((levelFloor % 2 == 0) ? SQUARE_SPEED : -SQUARE_SPEED, -JUMP_FORCE));*/
			playerBody->applyImpulse(Vec2(0, -JUMP_FORCE));
			//playerBody->setGravityEnable(true);

			float jumpAngle = levelFloor % 2 == 0 ? -20 : 20;
			auto rotateTo = RotateTo::create(JUMP_TIME*2, jumpAngle);
			auto rotateTo2 = RotateTo::create(JUMP_TIME*4, 0);
			auto seq = Sequence::create(rotateTo, rotateTo2, nullptr);
			theSquare->runAction(seq);

		}
		//theSquare->setRotation(-30);

	}
}

void GameScene::createFloor(int floor, std::vector<Barrier> floorLevelWall) {
	for (int i = 0; i < floorLevelWall.size(); i++) {
		auto spike = Sprite::create("sprites/pattern4.png");
		spike->setAnchorPoint(Vec2(0.5, 0));
		spike->setContentSize(Size(floorLevelWall[i].width, floorLevelWall[i].height));
		spike->setPosition(Vec2(
			floorX + floorLevelWall[i].x,
			visibleSize.height-floorY[floor]));

		auto spikeBody = PhysicsBody::createBox(Size(
			//floor->getContentSize().width-100, 
			spike->getContentSize().width,
			spike->getContentSize().height),
			PhysicsMaterial(0.0f, 0.0f, 0.0f));
		spikeBody->setDynamic(false);
		spikeBody->setContactTestBitmask(true);
		spikeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
		spike->setPhysicsBody(spikeBody);

		this->addChild(spike, 2);

	}
}

void GameScene::createWorldBounds() {

	auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width+40, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);
	edgeBody->setDynamic(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
}

void GameScene::createLevels() {
	squareColor.reserve(floorY.size());
	for (int i = 0; i < floorY.size(); i++) {

		std::vector<Color3B> colorsArray(levelColors.begin(), levelColors.end());

		auto bg = Sprite::create("sprites/maingame/background.jpg");
		bg->setAnchorPoint(Vec2(0,1));
		bg->setPosition(Vec2(floorX, visibleSize.height- (floorY[i]-LEVEL_HEIGHT)));
		bg->setOpacity(255 * 0.5);
		this->addChild(bg,1);

		squareColor.push_back(Helper4Array::getInstance()->removeRandomItemFromVector(colorsArray));
		bg->setColor(Helper4Array::getInstance()->removeRandomItemFromVector(colorsArray));

		auto floor = Sprite::create("sprites/maingame/floor.jpg");
		this->addChild(floor,2);
		floor->setAnchorPoint(Vec2(0, 1));
		floor->setPosition(Vec2(floorX,visibleSize.height-floorY[i]));
		//enable physic body for floor
		
		auto floorBody = PhysicsBody::createBox(Size(
			//floor->getContentSize().width-100, 
			floor->getContentSize().width+100, 
			floor->getContentSize().height),
			PhysicsMaterial(0.0f, 0.0f, 0.0f));
		floorBody->setDynamic(false);
		floorBody->setContactTestBitmask(true);
		floorBody->setCollisionBitmask(GOURND_COLLISION_BITMASK_PLAY);
		floor->setPhysicsBody(floorBody);

		//create floor at level i
		createFloor(i, gameLevels[i]);

	}
}


bool GameScene::onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) {
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	return true;
}


void GameScene::onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) {
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();


	if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			GOURND_COLLISION_BITMASK_PLAY == b->getCollisionBitmask()) ||
			(GOURND_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {
		/*theSquare->getPhysicsBody()->setVelocity(
			Vec2((levelFloor % 2 == 0) ? SQUARE_SPEED : -SQUARE_SPEED, 0));*/
	}
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	//// save the velocity, ignore the direction of velocity, only save the length
	//float* v = new float[2];
	//v[0] = a->getVelocity().length();
	//v[1] = b->getVelocity().length();

	//contact.setData(v);

	if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			BOUND_COLLISION_BITMASK == b->getCollisionBitmask()) ||
			(BOUND_COLLISION_BITMASK == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {
		// increasing floor number or setting it back to zero
		levelFloor = (levelFloor + 1) % floorY.size();
		placeSquare();
		return false;
	} else if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) ||
			(OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {

		playerDied();

		return false;
	}
	else if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			GOURND_COLLISION_BITMASK_PLAY == b->getCollisionBitmask()) ||
			(GOURND_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {

		canJump = true;
	}


	return true;
}

void GameScene::onContactSeperate(PhysicsContact& contact)
{
	//auto a = contact.getShapeA()->getBody();
	//auto b = contact.getShapeB()->getBody();

	//// restore the velocity, keep the direction of the velocity.
	//float* v = (float*)contact.getData();
	//auto va = a->getVelocity();
	//auto vb = b->getVelocity();
	//va.normalize();
	//vb.normalize();
	//a->setVelocity(va * v[0]);
	//b->setVelocity(vb * v[1]);


	//delete v;
}

void GameScene::placeSquare(){
	resetFloor(levelFloor - 1);

	//// adjusting hero speed according to floor number: from left to right on even floors, from right to left on odd floors
	//theSquare->getPhysicsBody()->setVelocity(Vec2((levelFloor % 2 == 0) ? SQUARE_SPEED : -SQUARE_SPEED, 0));

	//theSquare->setPosition(Vec2(
	//	(levelFloor % 2 == 0) ? floorX : floorX + FLOOR_WIDTH,
	//	visibleSize.height-(floorY[levelFloor] - SQUARE_SIZE / 2)));

	createTheSquare();

	theSquare->setColor(squareColor[levelFloor]);
	// theSquare can jump again
	canJump = true;

	//theSquare->getPhysicsBody()->setVelocity(Vec2::ZERO);

	theSquare->stopAllActions();
	theSquare->setRotation(0); 
	auto rotateTo2 = RotateTo::create(0, 0);
	theSquare->runAction(rotateTo2);
}

void GameScene::resetFloor(int floor) {

}

void GameScene::playerDied() {
	if (isDead) {
		return;
	}

	this->removeChild(theSquare);
	//soundController.PlayLooseSound();
	cocos2d::log("player died");
	isDead = true;
	popupController.CreatePopupGameOver(this, score, maxScore);
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
		info.link = "https://www.facebook.com/Rotate-Defense-577118195818190/";
		//info.link = "https://play.google.com/store/apps/details?id=com.donick.rotatebox";
		info.title = "Rotate Defense!";
		info.text = scoreStr->getCString();
		info.image = "https://raw.githubusercontent.com/tuynumemories/privacygame/master/levelUp.png";
		sdkbox::PluginFacebook::dialog(info);
#endif

	}
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

void GameScene::GoToGameScene(float dt) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}