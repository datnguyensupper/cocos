#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"
#include "Constant/PPEnums.h"

class SoundManager
{
private:
	int backgroundID;
    int lastSoundStopID = -1;

	std::set<int> aEffectPlaying;

	SoundManager();
	static SoundManager* s_instance;
	bool _canPlayBackgroundMusic;
	bool _canPlaySoundEffect;

	int idSoundEffectLuckyBoxChestBounce = -1;
	int idSoundEffectLuckyBoxChestShake = -1;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static SoundManager* getInstance();

	/**
	* 2017-02-27: Kiet: destructor
	*/
	~SoundManager();
	/// <summary>
	/// set can play background music
	/// </summary>
	/// <param name="canPlayBackgroundMusic"></param>
	void setCanPlayBackgroundMusic(bool canPlayBackgroundMusic);
	/// <summary>
	/// set can play sound effect
	/// </summary>
	/// <param name="canPlaySoundEffect"></param>
	void setCanPlaySoundEffect(bool canPlaySoundEffect);
	/// <summary>
	/// check can play background music
	/// </summary>
	/// <returns></returns>
	bool getCanPlayBackgroundMusic();
	/// <summary>
	/// check can play sound effect
	/// </summary>
	/// <returns></returns>
	bool getCanPlaySoundEffect();

	/// <summary>
	/// Play background music base on what your current scene
	/// </summary>
	int playBackgroundMusic(ppEnum::GameScene scene = ppEnum::GameScene::Lobby);
	/// <summary>
	/// stop background sound
	/// </summary>
	void stopBackgroundMusic();
	/// <summary>
	/// play Sound Effect
	/// </summary>
	/// <param name="pszFilePath">sound path</param>
	/// <param name="isLoop">is loop</param>
	/// <param name="pitch">volumn: 0->1</param>
	/// <returns>sound id</returns>
	/// <summary>
	int playSoundEffect(const std::string& pszFilePath, bool isBgMusic, bool isLoop, float pitch);
	/// <summary>
	/// set volumn for sound
	/// </summary>
	/// <param name="soundID">soud id</param>
	/// <param name="volume">volumn</param>
	void setVolume(int soundID, float volume);
	int playSound(const std::string& filePath, bool loop, float volume = 1.0f);
	/// <summary>
	/// stop sound effect with id
	/// </summary>
	/// <param name="effect">id</param>
	void stopSound(int effect);
	/// <summary>
	/// stop all sound effect
	/// </summary>
	void stopAllSoundEffect();
	/// <summary>
	/// stop all sound background and effect
	/// </summary>
	void stopAll();
	/// <summary>
	/// preload sound
	/// </summary>
	/// <param name="path">path of sound</param>
	/// <param name="callback">callback when done</param>
	void preload(const std::string& path, const std::function<void(bool isSucess)> callback);
	/// <summary>
	/// clear sound cache with path
	/// </summary>
	/// <param name="path"></param>
	void uncache(const std::string& path);
	/// <summary>
	/// clear cache all sound
	/// </summary>
	void uncacheAll();

	/// <summary>
	/// stop sound effect
	/// </summary>
	void stopSoundEffectLuckyBoxChestBounce();
	void stopSoundEffectLuckyBoxChestShake();

	/// <summary>
	/// play Sound Effect
	/// </summary>
	/// <param name="isLoop">is loop</param>
	/// <param name="pitch">volumn: 0->1</param>
	/// <returns>sound id</returns>
	void playSoundEffectIncreaseCoin(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectDecreaseCoin(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectOpenOrClosePopup(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectOpenShopPopup(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectCoinDrop(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectReceiveCoin(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectIncludeCoin(bool isLoop = false, float pitch = 1.0f);
	void playSoundEffectDailyWheelBonusSpin(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyWheelStart(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyWheelSpin(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyWheelStop(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckySpinStart(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckySpinReelStop(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckySpinStop(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyBoxChestBounce(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyBoxChestOpen(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectLuckyBoxChestShake(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectPiggyBankBreakPig(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectPiggyBankBreakPig2(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectPiggyBankCrackPig(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectPiggyBankCoinShake(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectPiggyBankFinish(bool isLoop = false, float pitch = 1.0f);
	int playSoundEffectMascotNoti(bool isLoop = false, float pitch = 1.0f);
};