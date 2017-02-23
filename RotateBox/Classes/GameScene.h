#pragma once

#include "cocos2d.h"
#include "EnemyController.h"
#include "PopupController.h"
#include "SoundController.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void restartGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	void shareFacebook(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
private:
	void createPlayer();
	void createWorldBounds();
	void spawnEnemy(float dt);

	void handleTouchController();
	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void onContactSeparate(cocos2d::PhysicsContact & contact);
	void GoToGameScene(float dt);
	void playerDied();
	void updateTextScore();

	cocos2d::Sprite *playerRed;
	cocos2d::Sprite *playerBlue;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	EnemyController enemyController;
	PopupController popupController;
	SoundController soundController;

	cocos2d::Vec2 lastTouchLocation;
	cocos2d::CCProgressTimer* difficultLevelProgress;

	cocos2d::LabelTTF *scoreText;
	int score;
	cocos2d::LabelTTF *maxScoreText;
	int maxScore;

	bool isDied = false;
	float enemySpeed;
};

