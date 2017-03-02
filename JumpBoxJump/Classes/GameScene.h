#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PopupController.h"
#include "SoundController.h"
#include "GameLevelController.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void updateTextScore();
	void createTheSquare();
	void createLevels();
	void createWorldBounds();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeperate(cocos2d::PhysicsContact& contact);
	bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
	void onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
	void placeSquare();
	void resetFloor(int floor);
	void resetSquarePosition(float dt);
	void resetSquareDirection();
	void squareJump();
	void playerDied();
	void shareFacebook(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	void restartGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	void GoToGameScene(float dt);
	void createEmitters();
	void update(float) override;

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::vector<cocos2d::Node*> arrayOfGroupEachFloorLevel;
	int floorX = 0;
	std::vector<int> floorY;
	std::vector<cocos2d::Color3B> squareColor;
	std::vector<cocos2d::Color3B> levelColors;
	bool isDead = false;
	int levelFloor = 0;
	cocos2d::Node* theSquare;
	cocos2d::ParticleSystemQuad* particleFuel;
	cocos2d::Sprite* theSquareGraphic;
	bool canJump = true;
	cocos2d::MoveTo jumpTween;
	cocos2d::CCParticleExplosion * dieParticle;

	cocos2d::CCLabelBMFont *scoreText;
	int score = 0;
	cocos2d::CCLabelBMFont *maxScoreText;
	int maxScore = 0;
	int gameDirection = 0;


	PopupController popupController;
	SoundController * soundController;
	GameLevelController gameLevelController;
};

#endif // __GAME_SCENE_H__
