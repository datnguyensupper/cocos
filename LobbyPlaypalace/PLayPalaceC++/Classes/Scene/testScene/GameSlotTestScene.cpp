#include "GameSlotTestScene.h"
#include "Manager/FileManager/SlotsGameDownloadFileManager.h"
#include "Manager/SoundManager.h"
#include "Custom/GameSlot/ButtonDownloadGameSlot.h"
#include "Constant/Defination.h"
#include "Configs.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
Scene* GameSlotTestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = BaseScene::create();
    scene->setTag(ppEnum::GameScene::Lobby);
    
    // 'layer' is an autorelease object
    auto layer = GameSlotTestScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return (Scene*)scene;
}

// on "init" you need to initialize your instance
bool GameSlotTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/*test:know what your scene*/
	auto label = Label::createWithSystemFont("GAME SLOT TEST SCENE", "Arial", 96);
	label->setColor(Color3B::BLUE);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(label, 1);

	/*test:Play background music*/
	SoundManager::getInstance()->stopBackgroundMusic();

	
	//DownloadFileManager::getInstance()->downloadFileWithURLAndSave2Device([=](std::string filePath) {
	//	//Texture2D * texture = new  Texture2D();
	//	//texture->initWithImage(image);

		//auto spriteTest = Sprite::createWithTexture(texture);
	//});
	createGameSlotUI();
	createParticalSnow();

    return true;
}

void GameSlotTestScene::createParticalSnow() {
	CCParticleSnow* particle = CCParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("test/snowflakes.png"));
	particle->setTotalParticles(800);
	particle->setDuration(kCCParticleDurationInfinity);
	particle->setStartSize(20);
	particle->setStartSizeVar(50);
	particle->setEndSize(5);
	particle->setEndSizeVar(0);
	particle->setSpeed(200);
	particle->setSpeedVar(100);
	particle->setGravity(ccp(-20, -70));
	particle->setLife(5.0f);
	particle->setLifeVar(2.0f);
	particle->setEmissionRate(100);
	CCSize a = CCDirector::sharedDirector()->getWinSize();
	particle->setAutoRemoveOnFinish(true);
	particle->setPosition(CCPoint(a.width / 2, a.height + 10));
	particle->setPosVar(ccp(a.width / 2 + 50, 0));

	//ccBlendFunc tBlendFunc = { GL_FUNC_ADD, GL_ONE };
	particle->setBlendAdditive(true);
	//particle->setCas

	this->addChild(particle, 20);
}


void GameSlotTestScene::createGameSlotUI() {

	// REAL DOWNLOAD SLOT GAME
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x - 600, visibleSize.height / 2 + origin.y + 330),
		GAME_SLOT_ID_NEZHA,
		"img/body/slotGameIcon/WebGame/40.png");
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height / 2 + origin.y + 300),
		GAME_SLOT_ID_GOLDENEGG,
		"img/body/slotGameIcon/WebGame/41.png");
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y + 300),
		GAME_SLOT_ID_PHARAOH,
		"img/body/slotGameIcon/WebGame/42.png");
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x + 00, visibleSize.height / 2 + origin.y + 300),
		GAME_SLOT_ID_BOXING,
		"img/body/slotGameIcon/WebGame/43.png");
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y+300),
		GAME_SLOT_ID_ROMANEMPIRE,
		"img/body/slotGameIcon/WebGame/44.png");
	createGameSlotUIBtn(
		Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 300),
		GAME_SLOT_ID_DEEPBLUE,
		"img/body/slotGameIcon/WebGame/54.png");


	// BACKGROUND DOWNLOAD SLOT GAME
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x - 600, visibleSize.height / 2 + origin.y + 0),
		GAME_SLOT_ID_NEZHA,
		"img/body/slotGameIcon/WebGame/40.png");
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height / 2 + origin.y + 0),
		GAME_SLOT_ID_GOLDENEGG,
		"img/body/slotGameIcon/WebGame/41.png");
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y + 0),
		GAME_SLOT_ID_PHARAOH,
		"img/body/slotGameIcon/WebGame/42.png");
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x + 00, visibleSize.height / 2 + origin.y + 0),
		GAME_SLOT_ID_BOXING,
		"img/body/slotGameIcon/WebGame/43.png");
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y+0),
		GAME_SLOT_ID_ROMANEMPIRE,
		"img/body/slotGameIcon/WebGame/44.png");
	createGameSlotUIBtnBackgroundThread(
		Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y + 0),
		GAME_SLOT_ID_DEEPBLUE,
		"img/body/slotGameIcon/WebGame/54.png");

}


void GameSlotTestScene::createGameSlotUIBtn(cocos2d::Vec2 position,std::string gameId, std::string gameImgPath) {

	ButtonDownloadGameSlot *playBtn = ButtonDownloadGameSlot::create(
		gameId,

		gameImgPath,
		gameImgPath);
	playBtn->setScale(0.7);
	playBtn->setPosition(position);
	
	playBtn->addTouchEventListener([playBtn](cocos2d::Ref* sender, ui::Widget::TouchEventType touchEvent) {
		if (touchEvent == ui::Widget::TouchEventType::ENDED) {
			playBtn->setTouchEnabled(false);
			playBtn->setTitleText("downloading...");
			cocos2d::log("onclick");
			SlotsGameDownloadFileManager::getInstance()->downloadSlotGameInMainUI(
				playBtn->_gameId,
				"",
				[playBtn](float progress, bool isFinish, bool isFail) {
				if (isFail) {
					playBtn->setTitleText("FAIL");
					playBtn->setTouchEnabled(true);
				}
				else if (!isFinish) {
					std::string progressStr = StringUtils::format("%.2f", progress) + "%";
					playBtn->setTitleText(progressStr);
				}
				else {//finish download
					playBtn->setTitleText("DONE");
					playBtn->setTouchEnabled(true);

					std::string testImagePath = DownloadFileManager::getInstance()->getGameSlotDirectoryGame(playBtn->_gameId);
					testImagePath.append("sprites/bg-loading.jpg");
					auto spriteTest = Helper4Sprite::createOptimizeSprite(testImagePath);
					if (spriteTest != nullptr) {
						spriteTest->setAnchorPoint(Vec2(0.5, 0.5));
						spriteTest->setScale(0.1);
						playBtn->addChild(spriteTest);
					}
				}

			});
		}
		
	});
	this->addChild(playBtn);

}


void GameSlotTestScene::createGameSlotUIBtnBackgroundThread(cocos2d::Vec2 position, std::string gameId, std::string gameImgPath) {

	ButtonDownloadGameSlot *playBtn = ButtonDownloadGameSlot::create(
		gameId,
		gameImgPath,
		gameImgPath);
	playBtn->setCascadeOpacityEnabled(true);
	playBtn->setScale(0.7);
	//playBtn->setOpacity(0.5*255);
	playBtn->setColor(Color3B::YELLOW);
	playBtn->setCascadeColorEnabled(true);
	playBtn->setPosition(position);

	playBtn->addTouchEventListener([playBtn](cocos2d::Ref* sender, ui::Widget::TouchEventType touchEvent) {
		if (touchEvent == ui::Widget::TouchEventType::ENDED) {
			playBtn->setTouchEnabled(false);
			playBtn->setTitleText("downloading...");
			cocos2d::log("onclick");
			SlotsGameDownloadFileManager::getInstance()->downloadSlotGameInBackgroundUI(
				playBtn->_gameId,
				playBtn->_gameVersion,
				[playBtn](float progress, bool isFinish, bool isFail) {
				if (isFail) {
					playBtn->setTitleText("FAIL");
					playBtn->setTouchEnabled(true);
				}
				else if (!isFinish) {
					std::string progressStr = StringUtils::format("%.2f", progress) + "%";
					playBtn->setTitleText(progressStr);
				}
				else {//finish download
					playBtn->setTitleText("DONE");
					playBtn->setTouchEnabled(true);

					std::string testImagePath = DownloadFileManager::getInstance()->getGameSlotDirectoryGame(playBtn->_gameId);
					testImagePath.append("sprites/bg-loading.jpg");
					auto spriteTest = Helper4Sprite::createOptimizeSprite(testImagePath);
					if (spriteTest != nullptr) {
						spriteTest->setAnchorPoint(Vec2(0.5, 0.5));
						spriteTest->setScale(0.1);
						playBtn->addChild(spriteTest);
					}
				}

			});
		}

	});
	this->addChild(playBtn);

}
