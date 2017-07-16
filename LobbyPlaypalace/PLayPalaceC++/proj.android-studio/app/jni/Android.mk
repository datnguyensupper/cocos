LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../../Classes/Constant/JSONFieldConstant.cpp \
../../../Classes/Constant/LanguageConstant.cpp \
../../../Classes/Constant/LobbyConstant.cpp \
../../../Classes/Constant/MessageConstant.cpp \
../../../Classes/Custom/Common/ButtonScaleChild.cpp \
../../../Classes/Custom/Common/CRadioButton.cpp \
../../../Classes/Custom/Common/CScratchSprite.cpp \
../../../Classes/Custom/Common/CSpinMachine.cpp \
../../../Classes/Custom/Common/CSpinWheel.cpp \
../../../Classes/Custom/Common/CustomRenderTexture.cpp \
../../../Classes/Custom/Common/LabelAutoSize.cpp \
../../../Classes/Custom/Common/ReuseItemListView_Horizontal.cpp \
../../../Classes/Custom/Common/ReuseItemListView_Vertical.cpp \
../../../Classes/Custom/Common/ToggleButton.cpp \
../../../Classes/Custom/GameSlot/ButtonDownloadGameSlot.cpp \
../../../Classes/Helper/Action/FShake.cpp \
../../../Classes/Helper/AnimationHelper.cpp \
../../../Classes/Helper/Helper4ParseJSON.cpp \
../../../Classes/Helper/Helper4Scene.cpp \
../../../Classes/Helper/Helper4Sprite.cpp \
../../../Classes/Helper/Helper4String.cpp \
../../../Classes/Helper/Helper4Time.cpp \
../../../Classes/Helper/KeyboardHelper.cpp \
../../../Classes/Manager/AnimationManager.cpp \
../../../Classes/Manager/DeviceManager.cpp \
../../../Classes/Manager/DownloadImageManager.cpp \
../../../Classes/Manager/InfoManager.cpp \
../../../Classes/Manager/LanguageManager.cpp \
../../../Classes/Manager/NetworkManager.cpp \
../../../Classes/Manager/PluginManager.cpp \
../../../Classes/Manager/PopupManager.cpp \
../../../Classes/Manager/ScaleManager.cpp \
../../../Classes/Manager/SoundManager.cpp \
../../../Classes/Manager/StrategyManager.cpp \
../../../Classes/Manager/FileManager/DownloadFileManager.cpp \
../../../Classes/Manager/FileManager/FileManager.cpp \
../../../Classes/Manager/FileManager/SlotsGameDownloadFileManager.cpp \
../../../Classes/Plugins/AdcolonyController.cpp \
../../../Classes/Plugins/FacebookController.cpp \
../../../Classes/Plugins/GamePlugin.cpp \
../../../Classes/Plugins/IAPController.cpp \
../../../Classes/Plugins/ImagePicker/ImagePicker.cpp \
../../../Classes/Plugins/ImagePicker/ImagePickerImpl.cpp \
../../../Classes/Scene/BaseScene.cpp \
../../../Classes/Scene/InitSessionScene.cpp \
../../../Classes/Scene/LobbyScene.cpp \
../../../Classes/Scene/LoginScene.cpp \
../../../Classes/Scene/LuckyWheelScene.cpp \
../../../Classes/Scene/testScene/CoinAnimationTestScene.cpp \
../../../Classes/Scene/testScene/GameSlotTestScene.cpp \
../../../Classes/SlotGame/GameSlotScene.cpp \
../../../Classes/SlotGame/base/constant/GameConstant.cpp \
../../../Classes/SlotGame/base/game/CBonusBase.cpp \
../../../Classes/SlotGame/base/game/CGameBase.cpp \
../../../Classes/SlotGame/base/game/CLoadingUI.cpp \
../../../Classes/SlotGame/base/game/CMainBase.cpp \
../../../Classes/SlotGame/base/interfaceUI/CFooter.cpp \
../../../Classes/SlotGame/base/interfaceUI/CGameEffectUI.cpp \
../../../Classes/SlotGame/base/interfaceUI/CInterfaceBase.cpp \
../../../Classes/SlotGame/base/interfaceUI/CReel.cpp \
../../../Classes/SlotGame/base/interfaceUI/CWinPanelBase.cpp \
../../../Classes/SlotGame/base/manager/Manager4Network.cpp \
../../../Classes/SlotGame/base/manager/Manager4Sound.cpp \
../../../Classes/SlotGame/base/settings/CSettings.cpp \
../../../Classes/SlotGame/base/settings/CSlotSettings.cpp \
../../../Classes/SlotGame/base/utils/CSpriteButton.cpp \
../../../Classes/SlotGame/base/utils/GameUtils.cpp \
../../../Classes/SlotGame/boxing/game/CDoubleUpBO.cpp \
../../../Classes/SlotGame/boxing/game/CGameBO.cpp \
../../../Classes/SlotGame/boxing/game/CMainBO.cpp \
../../../Classes/SlotGame/boxing/interfaceUI/CInterfaceBO.cpp \
../../../Classes/SlotGame/boxing/interfaceUI/CWinPanelBO.cpp \
../../../Classes/SlotGame/deepblue/game/CBonusFreeSpinDB.cpp \
../../../Classes/SlotGame/deepblue/game/CDoubleUpDB.cpp \
../../../Classes/SlotGame/deepblue/game/CGameDB.cpp \
../../../Classes/SlotGame/deepblue/game/CMainDB.cpp \
../../../Classes/SlotGame/deepblue/interfaceUI/CInterfaceDB.cpp \
../../../Classes/SlotGame/deepblue/interfaceUI/CJellyFishDB.cpp \
../../../Classes/SlotGame/deepblue/interfaceUI/CWinPanelDB.cpp \
../../../Classes/SlotGame/goldenegg/game/CBonusFreeSpinGE.cpp \
../../../Classes/SlotGame/goldenegg/game/CDoubleUpGE.cpp \
../../../Classes/SlotGame/goldenegg/game/CGameGE.cpp \
../../../Classes/SlotGame/goldenegg/game/CMainGE.cpp \
../../../Classes/SlotGame/goldenegg/interfaceUI/CCharacterGE.cpp \
../../../Classes/SlotGame/goldenegg/interfaceUI/CInterfaceGE.cpp \
../../../Classes/SlotGame/goldenegg/interfaceUI/CWinPanelGE.cpp \
../../../Classes/SlotGame/nezha/game/CBonusBattleLN.cpp \
../../../Classes/SlotGame/nezha/game/CBonusPalaceLN.cpp \
../../../Classes/SlotGame/nezha/game/CGameLN.cpp \
../../../Classes/SlotGame/nezha/game/CMainLN.cpp \
../../../Classes/SlotGame/nezha/interfaceUI/CCharacterLN.cpp \
../../../Classes/SlotGame/nezha/interfaceUI/CInterfaceLN.cpp \
../../../Classes/SlotGame/nezha/interfaceUI/CWinPanelLN.cpp \
../../../Classes/SlotGame/pharaoh/game/CBonusStage1PO.cpp \
../../../Classes/SlotGame/pharaoh/game/CBonusStage2PO.cpp \
../../../Classes/SlotGame/pharaoh/game/CGamePO.cpp \
../../../Classes/SlotGame/pharaoh/game/CMainPO.cpp \
../../../Classes/SlotGame/pharaoh/interfaceUI/CEaglePO.cpp \
../../../Classes/SlotGame/pharaoh/interfaceUI/CInterfacePO.cpp \
../../../Classes/SlotGame/pharaoh/interfaceUI/CReelPO.cpp \
../../../Classes/SlotGame/pharaoh/interfaceUI/CWinPanelPO.cpp \
../../../Classes/SlotGame/romanempire/game/CBonusRE.cpp \
../../../Classes/SlotGame/romanempire/game/CDoubleUpRE.cpp \
../../../Classes/SlotGame/romanempire/game/CGameRE.cpp \
../../../Classes/SlotGame/romanempire/game/CMainRE.cpp \
../../../Classes/SlotGame/romanempire/interfaceUI/CReelRE.cpp \
../../../Classes/SlotGame/romanempire/interfaceUI/CWinPanelRE.cpp \
../../../Classes/Util/CLoader.cpp \
../../../Classes/Util/PoolSystem.cpp \
../../../Classes/Util/UtilFunction.cpp \
../../../Classes/Views/Effects/AnimationCoinCrown.cpp \
../../../Classes/Views/Effects/CirclePink.cpp \
../../../Classes/Views/Effects/CoinFlare.cpp \
../../../Classes/Views/Effects/CrownFlareWithLensFlare.cpp \
../../../Classes/Views/Lobby/body/BodyLobbyLayout.cpp \
../../../Classes/Views/Lobby/body/ButtonGameSlot.cpp \
../../../Classes/Views/Lobby/bottom/BottomItem.cpp \
../../../Classes/Views/Lobby/bottom/BottomLobbyLayout.cpp \
../../../Classes/Views/Lobby/header/HeaderLobbyLayout.cpp \
../../../Classes/Views/Lobby/header/HeaderMagicItemBtn.cpp \
../../../Classes/Views/Login/MainLoginLayer.cpp \
../../../Classes/Views/Login/NotiLoginPopup.cpp \
../../../Classes/Views/Login/PPLoginLayer.cpp \
../../../Classes/Views/Login/ResetPassLayer.cpp \
../../../Classes/Views/Login/SignUpLayer.cpp \
../../../Classes/Views/LuckyWheel/LuckyWheelAnimationObject.cpp \
../../../Classes/Views/LuckyWheel/LuckyWheelLayout.cpp \
../../../Classes/Views/LuckyWheel/LuckyWheelShopPopup.cpp \
../../../Classes/Views/Popup/Achievement/AchievementCell.cpp \
../../../Classes/Views/Popup/Achievement/AchievementPopup.cpp \
../../../Classes/Views/Popup/DailyLuckySpin/DailyLuckySpinInfoPopup.cpp \
../../../Classes/Views/Popup/DailyLuckySpin/DailyLuckySpinPopup.cpp \
../../../Classes/Views/Popup/FBDailySpinPopup/DailyBonusWheelPopup.cpp \
../../../Classes/Views/Popup/FBDailySpinPopup/DailyBonusWheelResultPopup.cpp \
../../../Classes/Views/Popup/FBDailySpinPopup/DailyBonusWheelSpinPopup.cpp \
../../../Classes/Views/Popup/FriendPopup/CellFriend.cpp \
../../../Classes/Views/Popup/FriendPopup/CellInbox.cpp \
../../../Classes/Views/Popup/FriendPopup/CellLeaderboard.cpp \
../../../Classes/Views/Popup/FriendPopup/FriendPopup.cpp \
../../../Classes/Views/Popup/Shop/PurchaseItemNode.cpp \
../../../Classes/Views/Popup/Shop/ShopPopup.cpp \
../../../Classes/Views/Popup/AddRefereeCodePopup.cpp \
../../../Classes/Views/Popup/BasePopup.cpp \
../../../Classes/Views/Popup/ChangeNamePopup.cpp \
../../../Classes/Views/Popup/ComebackBonusMobilePopup.cpp \
../../../Classes/Views/Popup/DailyBonusStreakPopup.cpp \
../../../Classes/Views/Popup/DailyChallengePopup.cpp \
../../../Classes/Views/Popup/GameSlotInfoPopup.cpp \
../../../Classes/Views/Popup/GameUnlockedPopup.cpp \
../../../Classes/Views/Popup/LevelUpPopup.cpp \
../../../Classes/Views/Popup/LoadingAnimation.cpp \
../../../Classes/Views/Popup/LuckyBoxPopup.cpp \
../../../Classes/Views/Popup/MagicItemPopup.cpp \
../../../Classes/Views/Popup/MascotNotificationPopup.cpp \
../../../Classes/Views/Popup/MissingPopup.cpp \
../../../Classes/Views/Popup/NotificationPopup.cpp \
../../../Classes/Views/Popup/PiggyBankPopup.cpp \
../../../Classes/Views/Popup/ProfilePopup.cpp \
../../../Classes/Views/Popup/ScratchCardPopup.cpp \
../../../Classes/Views/Popup/SettingPopup.cpp \
../../../Classes/Views/Tutorial/Tutorial.cpp \
../../../Classes/AppDelegate.cpp \
../../../Classes/Configs.cpp \

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_SHARED_LIBRARIES := libadcolonyso \
libjsso
LOCAL_WHOLE_STATIC_LIBRARIES := PluginAdColony \
sdkbox \
PluginFacebook \
PluginIAP 

LOCAL_STATIC_LIBRARIES += android_native_app_glue

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginadcolony)
$(call import-module, ./pluginfacebook)
$(call import-module, ./pluginiap)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
