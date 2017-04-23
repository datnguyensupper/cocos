#include "Controller4Score.h"
#include "Definitions.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
Controller4Score* Controller4Score::s_instance = nullptr;

Controller4Score* Controller4Score::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new Controller4Score();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

Controller4Score::Controller4Score(){
	UserDefault * def = UserDefault::getInstance();
	maxScore = def->getIntegerForKey(CACHE_MAX_SCORE, 0);
}

void Controller4Score::updateMaxScore() {
	if (currentScore > maxScore) {
		UserDefault * def = UserDefault::getInstance();
		maxScore = currentScore;
		def->setIntegerForKey(CACHE_MAX_SCORE, maxScore);
	}
}

void Controller4Score::increaseCurrentScore(int _increaseAmount) {
	currentScore += _increaseAmount;
}

void Controller4Score::setCurrentScore(int _currentScore) {
	currentScore = _currentScore;
}