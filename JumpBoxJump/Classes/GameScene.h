#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PopupController.h"

struct Barrier {
	int width;
	int height;
	int x;
};

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	void createGameLevels();
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
	void squareJump();
	void createFloor(int floor, std::vector<Barrier> floorLevelWall);
	void playerDied();
	void shareFacebook(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	void restartGame(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	void GoToGameScene(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::vector<std::vector<Barrier>> gameLevels;
	std::vector<std::vector<Barrier>> gameLevelsRandom;
	std::vector<int> floorY;
	std::vector<cocos2d::Color3B> squareColor;
	int floorX = 0;
	std::vector<cocos2d::Color3B> levelColors;
	bool isDead = false;
	int levelFloor = 0;
	cocos2d::Node* theSquare;
	cocos2d::Sprite* theSquareGraphic;
	bool canJump = true;
	cocos2d::MoveTo jumpTween;

	cocos2d::CCLabelBMFont *scoreText;
	int score = 0;
	cocos2d::CCLabelBMFont *maxScoreText;
	int maxScore = 0;


	PopupController popupController;
};

#endif // __GAME_SCENE_H__
