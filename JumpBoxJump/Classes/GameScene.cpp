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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -SQUARE_GRAVITY));
	
    
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
    
	soundController = SoundController::getInstance();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	theSquare = nullptr;

	floorY = {112-EXTRA_HEIGHT,224 - EXTRA_HEIGHT,336 - EXTRA_HEIGHT,448 - EXTRA_HEIGHT };
	levelColors = {Color3B(232,29,98),Color3B(155,38,175),Color3B(32,149,242), Color3B(75,174,79),Color3B(254,234,58),Color3B(121,85,72),Color3B(95,124,138), };

	gameLevelController.createGameLevels();
	gameLevelController.setFloor(floorX,floorY);
	updateTextScore();
	createLevels();
	createTheSquare();
	createWorldBounds();
	soundController->PlayBackgroundMusic();
	soundController->CreateSoundControl(this);
	createEmitters();
	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	//contactListener->onContactPostSolve = CC_CALLBACK_2(GameScene::onContactPostSolve, this);
	//contactListener->onContactPreSolve = CC_CALLBACK_2(GameScene::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Add a "touch" event listener to our sprite
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* event)->bool {
		squareJump();
		return true;
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
		this->addChild(theSquare,20);
		//playerRed->setScaleX(2);

		particleFuel = ParticleSystemQuad::create("sprites/particle_fuel.plist");
		particleFuel->setTexture(TextureCache::sharedTextureCache()->addImage("sprites/particle_fuel.png"));
		theSquare->addChild(particleFuel, 200);

	}
	else {
		theSquare->getPhysicsBody()->removeFromWorld();
	}

	theSquare->setColor(squareColor[levelFloor]);
	theSquare->setRotation(0);
	this->scheduleOnce(schedule_selector(GameScene::resetSquarePosition), 0);
}

void GameScene::resetSquarePosition(float dt) {

	Vec2 squarePosition = Vec2((levelFloor % 2 == gameDirection) ? floorX + 20 : floorX + FLOOR_WIDTH - 20,
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
	playerBody->setVelocityLimit(450);
	playerBody->setRotationEnable(false);
	theSquare->setPhysicsBody(playerBody);

	resetSquareDirection();
}

void GameScene::resetSquareDirection() {

	particleFuel->setGravity(Vec2((levelFloor % 2 == gameDirection) ? -540 : 540, 0));
	particleFuel->setPosition(Vec2((levelFloor % 2 == gameDirection) ? 0 : 40, 10));
	theSquare->getPhysicsBody()->setVelocity(Vec2((levelFloor % 2 == gameDirection) ? SQUARE_SPEED : -SQUARE_SPEED, 0));

}

void GameScene::squareJump() {

	if (isDead) {
		return;
	}

	if (canJump) {

		soundController->PlayJumpSound();
		canJump = false;
		PhysicsBody * playerBody = theSquare->getPhysicsBody();
		if (playerBody != nullptr && playerBody->getVelocity().y < 1) {

			float velocity = -JUMP_FORCE;

			playerBody->setVelocity(Vec2((levelFloor % 2 == gameDirection) ? SQUARE_SPEED : -SQUARE_SPEED, velocity));
			//playerBody->applyImpulse(Vec2(0, -JUMP_FORCE));
			//playerBody->setGravityEnable(true);

			float jumpAngle = levelFloor % 2 == gameDirection ? -20 : 20;
			auto rotateTo = RotateTo::create(JUMP_TIME*2, jumpAngle);
			auto rotateTo2 = RotateTo::create(JUMP_TIME*4, 0);
			auto seq = Sequence::create(rotateTo, rotateTo2, nullptr);
			theSquare->runAction(seq);

		}
		//theSquare->setRotation(-30);

	}
}

void GameScene::createWorldBounds() {

	auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width+40, visibleSize.height), PhysicsMaterial(0.0f, 0.0f, 0.0f), 3);
	edgeBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);
	edgeBody->setDynamic(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
}

void GameScene::createLevels() {
	//squareColor.reserve(floorY.size());
	for (int i = 0; i < floorY.size(); i++) {
		arrayOfGroupEachFloorLevel.push_back(nullptr);

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
		Node *groupSpikeOfThisLevel = gameLevelController.createFloor(i,this);
		arrayOfGroupEachFloorLevel[i] = groupSpikeOfThisLevel;

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
			OBSTACLE_GOBACK_COLLISION_BITMASK == b->getCollisionBitmask()) ||
			(OBSTACLE_GOBACK_COLLISION_BITMASK == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {
		gameDirection = (gameDirection == 0)?1:0;
		resetSquareDirection();
		return false;
	}
	else if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			POINT_COLLISION_BITMASK == b->getCollisionBitmask()) ||
			(POINT_COLLISION_BITMASK == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {

		PhysicsBody * point =
			(POINT_COLLISION_BITMASK == a->getCollisionBitmask()) ? a : b;
		point->getNode()->removeFromParentAndCleanup(true);

		soundController->PlayCoinSound();
		score++;
		updateTextScore();

		return false;
	}
	else if (
		(PLAYER_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
			GOURND_COLLISION_BITMASK_PLAY == b->getCollisionBitmask()) ||
			(GOURND_COLLISION_BITMASK_PLAY == a->getCollisionBitmask() &&
				PLAYER_COLLISION_BITMASK_PLAY == b->getCollisionBitmask())) {
		PhysicsBody * playerBody = theSquare->getPhysicsBody();
		if (playerBody != nullptr) {
			playerBody->setVelocity(Vec2((levelFloor % 2 == gameDirection) ? SQUARE_SPEED : -SQUARE_SPEED, 0));
		}
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
	//theSquare->getPhysicsBody()->setVelocity(Vec2((levelFloor % 2 == gameDirection) ? SQUARE_SPEED : -SQUARE_SPEED, 0));

	//theSquare->setPosition(Vec2(
	//	(levelFloor % 2 == gameDirection) ? floorX : floorX + FLOOR_WIDTH,
	//	visibleSize.height-(floorY[levelFloor] - SQUARE_SIZE / 2)));

	createTheSquare();

	// theSquare can jump again
	canJump = true;

	//theSquare->getPhysicsBody()->setVelocity(Vec2::ZERO);

	theSquare->stopAllActions();
	theSquare->setRotation(0); 
	auto rotateTo2 = RotateTo::create(0, 0);
	theSquare->runAction(rotateTo2);
}

void GameScene::resetFloor(int floor) {
	if (floor < 0) {
		floor = floorY.size() - 1;
	}

	
	this->removeChild(arrayOfGroupEachFloorLevel[floor]);
	arrayOfGroupEachFloorLevel[floor] = nullptr;
	Node *groupSpikeOfThisLevel = gameLevelController.createFloorRandom(floor, this);
	arrayOfGroupEachFloorLevel[floor] = groupSpikeOfThisLevel;
	/*Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
		this->removeChild(arrayOfGroupEachFloorLevel[floor]);
	});*/
}

void GameScene::playerDied() {
	if (isDead) {
		return;
	}

	dieParticle->setPosition(theSquare->getPosition());
	dieParticle->resetSystem();

	soundController->PlayLooseSound();
	this->removeChild(theSquare);
	//soundController->PlayLooseSound();
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

#ifdef SDKBOX_ENABLED
		/*if (!sdkbox::PluginFacebook::isLoggedIn()) {
		sdkbox::PluginFacebook::login();
		}*/
		__String * scoreStr = __String::createWithFormat("Congratulations! You beat your personal record! Your new score is %i", maxScore);
		sdkbox::FBShareInfo info;
		info.type = sdkbox::FB_LINK;
		info.link = "https://www.facebook.com/Jump-Box-Jump-1617325158294542/";
		//info.link = "https://play.google.com/store/apps/details?id=com.donick.rotatebox";
		info.title = "Jump Box Jump!";
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


void GameScene::createEmitters() {
	
	//dieParticle = CCParticleExplosion::create();
	dieParticle = ParticleExplosion::create();
	dieParticle->setTexture(CCTextureCache::sharedTextureCache()->addImage("sprites/pattern4.png"));
	dieParticle->setPosition(Vec2(100, 100));
	dieParticle->setPosVar(ccp(20, 20));
	dieParticle->setTotalParticles(30);
	dieParticle->setDuration(0.2);
	dieParticle->setStartSize(5);
	dieParticle->setStartSizeVar(5);
	dieParticle->setEndSize(20);
	dieParticle->setEndSizeVar(3);
	dieParticle->setGravity(Vec2(0, -300));
	dieParticle->setLife(0.8f);
	dieParticle->setLifeVar(0);
	dieParticle->setEmissionRate(60);
	dieParticle->setSpeed(50);
	dieParticle->setSpeedVar(50);


	dieParticle->stopSystem();
	this->addChild(dieParticle, 20);
}

void GameScene::update(float) {

}
