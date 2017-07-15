#include "SoundManager.h"
#include "AudioEngine.h"
#include "Constant/Defination.h"
#include "ui/CocosGUI.h"
#include "Configs.h"
#include "Constant/PPEnums.h"
#include "SlotGame/base/manager/Manager4Sound.h"
#include <algorithm>

USING_NS_CC;
using namespace std;
using namespace experimental;
#pragma region init singleton
SoundManager* SoundManager::s_instance = nullptr;

SoundManager* SoundManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new SoundManager();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

SoundManager::~SoundManager()
{

}
SoundManager::SoundManager()
{
	_canPlayBackgroundMusic = UserDefault::getInstance()->getBoolForKey(STORING_KEY_CAN_PLAY_BACKGROUND_MUSIC,true);
	_canPlaySoundEffect = UserDefault::getInstance()->getBoolForKey(STORING_KEY_CAN_PLAY_SOUND_EFFECT,true);
}

void SoundManager::setCanPlayBackgroundMusic(bool canPlayBackgroundMusic) {
	_canPlayBackgroundMusic = canPlayBackgroundMusic;
	GameSlot::Manager4Sound::getInstance()->setState(canPlayBackgroundMusic);
	UserDefault::getInstance()->setBoolForKey(STORING_KEY_CAN_PLAY_BACKGROUND_MUSIC, _canPlayBackgroundMusic);
	UserDefault::getInstance()->flush();
}

void SoundManager::setCanPlaySoundEffect(bool canPlaySoundEffect) {
	_canPlaySoundEffect = canPlaySoundEffect;
	UserDefault::getInstance()->setBoolForKey(STORING_KEY_CAN_PLAY_SOUND_EFFECT, _canPlaySoundEffect);
	UserDefault::getInstance()->flush();
}

bool SoundManager::getCanPlayBackgroundMusic() {
	return _canPlayBackgroundMusic;
}

bool SoundManager::getCanPlaySoundEffect() {
	return _canPlaySoundEffect;
}

/// <summary>
/// Play background music base on what your current scene
/// </summary>
int SoundManager::playBackgroundMusic(ppEnum::GameScene scene) {
	if (!_canPlayBackgroundMusic) {
		return -1;
	}
	AudioEngine::stop(backgroundID);
	switch (scene)
	{
	case ppEnum::GameScene::Lobby: {
		backgroundID = AudioEngine::play2d(SOUND_BG_LOBBY, true);
		break;
	}
	case ppEnum::GameScene::LuckyWheel: {
		backgroundID = AudioEngine::play2d(SOUND_BG_LUCKY_WHEEL, true);
		break;
	}
	default:
		break;
	}
	return backgroundID;
}

void SoundManager::stopBackgroundMusic() {
	AudioEngine::stop(backgroundID);
}

int SoundManager::playSoundEffect(const std::string& pszFilePath, bool isLoop, float pitch) {
	if (!_canPlaySoundEffect) {
		return -1;
	}
	auto effectID = AudioEngine::play2d(pszFilePath, isLoop, pitch);
	if (effectID != AudioEngine::INVALID_AUDIO_ID) {
		aEffectPlaying.insert(effectID);
		AudioEngine::setFinishCallback(effectID, [this](int id, std::string name) {
			if (aEffectPlaying.find(id) != aEffectPlaying.end()){
				aEffectPlaying.erase(id);
			}
		});
	}
	return effectID;
}

void SoundManager::setVolume(int soundID, float volume)
{
	AudioEngine::setVolume(soundID, volume);
}

void SoundManager::stopSound(int effect)
{
	AudioEngine::stop(effect);
}

void SoundManager::stopAllSoundEffect() {

	for (auto id : aEffectPlaying) {
		AudioEngine::stop(id);
	}
	aEffectPlaying.clear();
}

void SoundManager::stopAll()
{
	this->stopBackgroundMusic();
	this->stopAllSoundEffect();
}

void SoundManager::preload(const std::string & path, const std::function<void(bool isSucess)> callback)
{
	AudioEngine::preload(path, callback);
}

void SoundManager::uncache(const std::string & path)
{
	AudioEngine::uncache(path);
}

void SoundManager::uncacheAll()
{
	AudioEngine::uncacheAll();
}

void SoundManager::playSoundEffectIncreaseCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_INCREASE_COIN, isLoop, pitch);
}

void SoundManager::playSoundEffectDecreaseCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_DECREASE_COIN, isLoop, pitch);
}

void SoundManager::playSoundEffectOpenOrClosePopup(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_OPEN_OR_CLOSE_POPUP, isLoop, pitch);
}

void SoundManager::playSoundEffectOpenShopPopup(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_OPEN_SHOP, isLoop, pitch);
}

void SoundManager::playSoundEffectCoinDrop(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_COIN_DROP, isLoop, pitch);
}

void SoundManager::playSoundEffectReceiveCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_RECEIVE_COIN, isLoop, pitch);
}

void SoundManager::playSoundEffectIncludeCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_INCLUDE_COIN, isLoop, pitch);
}

void SoundManager::playSoundEffectDailyWheelBonusSpin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_DAILY_WHEEL_BONUS_SPIN, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelStart(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_START, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelSpin(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_SPIN, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_STOP, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinStart(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_START, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinReelStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_SPIN_REEL_STOP, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_SPIN_STOP, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyBoxChestBounce(bool isLoop, float pitch) {
	idSoundEffectLuckyBoxChestBounce = this->playSoundEffect(SOUND_LUCKY_BOX_BOUNCE, isLoop, pitch);
	return idSoundEffectLuckyBoxChestBounce;
}
void SoundManager::stopSoundEffectLuckyBoxChestBounce() {
	if (idSoundEffectLuckyBoxChestBounce >= 0)
		stopSound(idSoundEffectLuckyBoxChestBounce);
}

int SoundManager::playSoundEffectLuckyBoxChestOpen(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_LUCKY_BOX_OPEN, isLoop, pitch);
}


int SoundManager::playSoundEffectLuckyBoxChestShake(bool isLoop, float pitch) {
	idSoundEffectLuckyBoxChestShake = this->playSoundEffect(SOUND_LUCKY_BOX_SHAKE, isLoop, pitch);
	return idSoundEffectLuckyBoxChestShake;
}
void SoundManager::stopSoundEffectLuckyBoxChestShake() {
	if (idSoundEffectLuckyBoxChestShake >= 0)
		stopSound(idSoundEffectLuckyBoxChestShake);
}

int SoundManager::playSoundEffectPiggyBankBreakPig(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_BREAK_PIG, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankBreakPig2(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_BREAK_PIG_2, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankCrackPig(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_CRACK_PIG, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankCoinShake(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUNG_PIGGY_BANK_COIN_SHAKE, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankFinish(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_FINISH, isLoop, pitch);
}

int SoundManager::playSoundEffectMascotNoti(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_MASCOT_NOTIFICATION, isLoop, pitch);
}


