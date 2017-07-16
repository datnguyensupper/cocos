#include "Manager4Sound.h"
#include "../game/CMainBase.h"
#include "../game/CGameBase.h"
#include "Manager/SoundManager.h"
USING_NS_CC;
namespace GameSlot {
	static Manager4Sound *_sharedManager4Sound = nullptr;
	Manager4Sound* Manager4Sound::getInstance()
	{
		if (!_sharedManager4Sound)
		{
			_sharedManager4Sound = new (std::nothrow) Manager4Sound();
		}

		return _sharedManager4Sound;
	}

	Manager4Sound::Manager4Sound(): oMain(nullptr),
		backGroundID(-1),
		animationID(-1),
		reelSpinID(-1),
		totalWinID(-1),
		bSoundEnabled(true)
	{

	}

	Manager4Sound::~Manager4Sound()
	{

	}

	void Manager4Sound::turnOffAllSound()
	{
		SoundManager::getInstance()->stopAll();
	}

	void Manager4Sound::setGame(CMainBase * oMain, const std::map<std::string, std::string>& res)
	{
		this->oMain = oMain;  
		this->resSound = res;
		this->bSoundEnabled = SoundManager::getInstance()->getCanPlayBackgroundMusic();
	}

	void Manager4Sound::reset()
	{
		if (this->bSoundEnabled) {
			this->playBackgroundMusic();
		}
		else {
			this->turnOffAllSound();
		}
	}

	void Manager4Sound::setState(bool bEnabled)
	{
		this->bSoundEnabled = bEnabled;

		if (this->resSound.empty()) return;

		if (this->bSoundEnabled) {
			this->playBackgroundMusic();
		}
		else {
			this->turnOffAllSound();
		}
	}

	int Manager4Sound::playBackgroundMusic()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		std::string soundFile = "";
		switch (this->oMain->getGame()->getCurrentType()) {
		case GAME_TYPE::MAIN_GAME:
			soundFile = this->resSound["main_game"];
			break;
		case GAME_TYPE::FREE_SPIN:
			soundFile = this->resSound["free_spin"];
			break;
		case GAME_TYPE::BONUS:
			switch (this->oMain->getGame()->getBonusActive())
			{
			case BONUS_TYPE::BONUS_TYPE_3:
				soundFile = this->resSound["bonus_3"];
				break;
			case BONUS_TYPE::BONUS_TYPE_4:
				soundFile = this->resSound["bonus_4"];
				break;
			}
			break;
		case GAME_TYPE::DOUBLE_UP:
			soundFile = this->resSound["double_up"];
			break;
		}

		SoundManager::getInstance()->stopSound(backGroundID);
		backGroundID = SoundManager::getInstance()->playSoundEffect(soundFile,true, true, 0.5f);
		return backGroundID;
	}

	void Manager4Sound::setVolumeBackgroundMusic(float volume)
	{
		SoundManager::getInstance()->setVolume(volume, min(volume, 0.5f));
	}

	int Manager4Sound::playSpin()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		return SoundManager::getInstance()->playSoundEffect(this->resSound["spin"],false,false,1.0f);
	}

	int Manager4Sound::playReelSpin()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("reel_spin") != this->resSound.end()) {
			reelSpinID = SoundManager::getInstance()->playSoundEffect(this->resSound["reel_spin"],false, true,1.0f);
		}
		return reelSpinID;
	}

	void Manager4Sound::stopReelSpin()
	{
		this->stopEffect(reelSpinID);
	}

	int Manager4Sound::playReelStop()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		return SoundManager::getInstance()->playSoundEffect(this->resSound["reel_stop"], false, false, 1.0f);
	}

	int Manager4Sound::playScatterStop()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("scatter_stop") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["scatter_stop"], false, false, 1.0f);
		}
		else {
			return this->playReelStop();
		}
	}

	int Manager4Sound::playWildStop()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("wild_stop") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["wild_stop"], false, false, 1.0f);
		}
		else {
			return this->playReelStop();
		}
	}

	int Manager4Sound::playBonusStop(int bonusID)
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("bonus_" + ToString(bonusID) + "_stop") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["bonus_" + ToString(bonusID) + "_stop"], false, false, 1.0f);
		}
		else {
			return this->playReelStop();
		}
	}

	int Manager4Sound::playSymbolAnimation(int iSymbol)
	{
		if (!bSoundEnabled) {
			return -1;
		}
		animationID = SoundManager::getInstance()->playSoundEffect(this->resSound["symbol_" + ToString(iSymbol)], false, false, 1.0f);
		this->setVolumeBackgroundMusic(0.1f);
		return animationID;
	}

	void Manager4Sound::stopSymolAnimation()
	{
		this->setVolumeBackgroundMusic(1.0f);
		this->stopEffect(animationID);
	}

	int Manager4Sound::playTotalWin()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		totalWinID = SoundManager::getInstance()->playSoundEffect(this->resSound["total_winning"], false, false, 1.0f);
		return totalWinID;
	}

	void Manager4Sound::stopTotalWin()
	{
		this->stopEffect(totalWinID);
	}

	int Manager4Sound::playBtnDoubleUpClicked()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("double_up_clicked") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["double_up_clicked"], false, false, 1.0f);
		}
		return -1;
	}

	int Manager4Sound::playBtnBonusType3Clicked()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("bonus_3_clicked") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["bonus_3_clicked"], false, false, 1.0f);
		}
		return -1;
	}

	int Manager4Sound::playBtnBonusType4Clicked()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("bonus_4_clicked") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["bonus_4_clicked"], false, false, 1.0f);
		}
		return -1;
	}

	int Manager4Sound::playDoubleUpWin()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("double_up_win") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["double_up_win"], false, false, 1.0f);
		}
		return -1;
	}

	int Manager4Sound::playDoubleUpLose()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		if (this->resSound.find("double_up_lose") != this->resSound.end()) {
			return SoundManager::getInstance()->playSoundEffect(this->resSound["double_up_lose"], false, false, 1.0f);
		}
		return -1;
	}

	int Manager4Sound::playWinEffectSound()
	{
		if (!bSoundEnabled) {
			return -1;
		}
		return SoundManager::getInstance()->playSoundEffect("sound/megaBigWin.mp3", false, false, 1.0f);
	}

	int Manager4Sound::playEffect(const std::string & file, bool isLoop)
	{
		if (!bSoundEnabled) {
			return -1;
		}
		return SoundManager::getInstance()->playSoundEffect(file,false, isLoop,1.0f);
	}

	void Manager4Sound::stopEffect(int id)
	{
		SoundManager::getInstance()->stopSound(id);
	}

	
	void Manager4Sound::release()
	{
		for (auto res : resSound) {
			SoundManager::getInstance()->uncache(res.second);
		}

		CC_SAFE_DELETE(_sharedManager4Sound);
	}
}