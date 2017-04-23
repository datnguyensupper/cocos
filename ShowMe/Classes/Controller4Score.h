#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"

class Controller4Score
{
private:

	int currentScore = 0;
	int maxScore = 0;

	Controller4Score();
	static Controller4Score* s_instance;

public:
	static Controller4Score* getInstance();
	
	void updateMaxScore();
	void increaseCurrentScore(int _increaseAmount);
	void setCurrentScore(int _currentScore);
	int getCurrentScore() { return currentScore; }
	int getMaxScore() { return maxScore; }
};