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

	switch (scene)
	{
	case ppEnum::GameScene::Lobby: {
		stopSound(backgroundID);
		backgroundID = playSound(SOUND_BG_LOBBY, true);
		break;
	}
	case ppEnum::GameScene::LuckyWheel: {
        stopSound(backgroundID);
		backgroundID = playSound(SOUND_BG_LUCKY_WHEEL, true);
		break;
	}
	default:
		break;
	}
	return backgroundID;
}

void SoundManager::stopBackgroundMusic() {
    stopSound(backgroundID);
}

int SoundManager::playSoundEffect(const std::string& pszFilePath, bool isBgMusic, bool isLoop, float pitch) {
	if ((!_canPlaySoundEffect && !isBgMusic) || (!_canPlayBackgroundMusic && isBgMusic)) {
		return -1;
	}

	auto effectID = playSound(pszFilePath, isLoop, pitch);
	if (effectID != AudioEngine::INVALID_AUDIO_ID) {
		if (!isBgMusic) {
			aEffectPlaying.insert(effectID);
		}else {
			backgroundID = effectID;
		}
		AudioEngine::setFinishCallback(effectID, [this,pszFilePath,isBgMusic,isLoop,pitch](int id, std::string name) {
            log("AudioEngine::setFinishCallback %i", id);
			if (aEffectPlaying.find(id) != aEffectPlaying.end()){
				aEffectPlaying.erase(id);
            }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            if(isLoop){
                stopSound(id);
                playSoundEffect(pszFilePath,isBgMusic,isLoop,pitch);
            }
#endif
		});
	}
	return effectID;
}

void SoundManager::stopAllSoundEffect() {


    log("stopAllSoundEffect start");
	for (auto id : aEffectPlaying) {
        stopSound(id);
	}
	aEffectPlaying.clear();
    log("stopAllSoundEffect finish");
}

void SoundManager::stopAll() {
	this->stopBackgroundMusic();
	this->stopAllSoundEffect();
}


int SoundManager::playSound(const std::string& filePath, bool loop, float volume){
    int soundId = AudioEngine::play2d(filePath, loop, volume);
    log("SoundManager::playSound %s id %i", filePath.c_str(), soundId);
    return soundId;
}

void SoundManager::setVolume(int soundID, float volume) {
    log("SoundManager::setVolume %i", soundID);
    AudioEngine::setVolume(soundID, volume);
}

void SoundManager::stopSound(int effect) {
    if(effect < 0 || lastSoundStopID == effect) return;
    log("SoundManager::stopSound %i", effect);

    float delta = AudioEngine::getDuration(effect) - AudioEngine::getCurrentTime(effect);
    if(delta <= 0) return;
    log("SoundManager::sound duration - current %f ", delta);
    if(AudioEngine::getState(effect) == AudioEngine::AudioState::PLAYING) {
//        AudioEngine::pause(effect);
        AudioEngine::stop(effect);
        log("SoundManager::stopSound %i success", effect);
        lastSoundStopID = effect;
    }
}


void SoundManager::preload(const std::string & path, const std::function<void(bool isSucess)> callback) {
    log("SoundManager::preload %s", path.c_str());
	AudioEngine::preload(path, callback);
}

void SoundManager::uncache(const std::string & path) {
    log("SoundManager::uncache %s", path.c_str());
	AudioEngine::uncache(path);
}

void SoundManager::uncacheAll() {
    log("SoundManager::uncacheAll");
	AudioEngine::uncacheAll();
}

void SoundManager::playSoundEffectIncreaseCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_INCREASE_COIN,false, isLoop, pitch);
}

void SoundManager::playSoundEffectDecreaseCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_DECREASE_COIN, false, isLoop, pitch);
}

void SoundManager::playSoundEffectOpenOrClosePopup(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_OPEN_OR_CLOSE_POPUP, false, isLoop, pitch);
}

void SoundManager::playSoundEffectOpenShopPopup(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_OPEN_SHOP, false, isLoop, pitch);
}

void SoundManager::playSoundEffectCoinDrop(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_COIN_DROP, false, isLoop, pitch);
}

void SoundManager::playSoundEffectReceiveCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_RECEIVE_COIN, false, isLoop, pitch);
}

void SoundManager::playSoundEffectIncludeCoin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_INCLUDE_COIN, false, isLoop, pitch);
}

void SoundManager::playSoundEffectDailyWheelBonusSpin(bool isLoop, float pitch)
{
	this->playSoundEffect(SOUND_DAILY_WHEEL_BONUS_SPIN, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelStart(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_START, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelSpin(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_SPIN, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyWheelStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_STOP, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinStart(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_WHEEL_START, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinReelStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_SPIN_REEL_STOP, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckySpinStop(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_LUCKY_SPIN_STOP, false, isLoop, pitch);
}

int SoundManager::playSoundEffectLuckyBoxChestBounce(bool isLoop, float pitch) {
	idSoundEffectLuckyBoxChestBounce = this->playSoundEffect(SOUND_LUCKY_BOX_BOUNCE, false, isLoop, pitch);
	return idSoundEffectLuckyBoxChestBounce;
}
void SoundManager::stopSoundEffectLuckyBoxChestBounce() {
	if (idSoundEffectLuckyBoxChestBounce >= 0)
		stopSound(idSoundEffectLuckyBoxChestBounce);
}

int SoundManager::playSoundEffectLuckyBoxChestOpen(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_LUCKY_BOX_OPEN, false, isLoop, pitch);
}


int SoundManager::playSoundEffectLuckyBoxChestShake(bool isLoop, float pitch) {
	idSoundEffectLuckyBoxChestShake = this->playSoundEffect(SOUND_LUCKY_BOX_SHAKE, false, isLoop, pitch);
	return idSoundEffectLuckyBoxChestShake;
}
void SoundManager::stopSoundEffectLuckyBoxChestShake() {
	if (idSoundEffectLuckyBoxChestShake >= 0)
		stopSound(idSoundEffectLuckyBoxChestShake);
}

int SoundManager::playSoundEffectPiggyBankBreakPig(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_BREAK_PIG, false, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankBreakPig2(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_BREAK_PIG_2, false, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankCrackPig(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_CRACK_PIG, false, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankCoinShake(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUNG_PIGGY_BANK_COIN_SHAKE, false, isLoop, pitch);
}

int SoundManager::playSoundEffectPiggyBankFinish(bool isLoop, float pitch) {
	return this->playSoundEffect(SOUND_PIGGY_BANK_FINISH, false, isLoop, pitch);
}

int SoundManager::playSoundEffectMascotNoti(bool isLoop, float pitch)
{
	return this->playSoundEffect(SOUND_MASCOT_NOTIFICATION, false, isLoop, pitch);
}


