#pragma once

#include "cocos2d.h"
class VungleListener
{
public:
    /*!
     * called when AdColony is finished loading.
     */
    virtual void onAdStart() = 0;
    /*!
     * reward was received.
     */
    virtual void onAdUnavailable(const std::string& reason) = 0;
    /*!
     * showing an ad has started.
     */
    virtual void onAdEnd(bool wasSuccessfulView) = 0;
    /*!
     * showing an ad has finished.
     */
    virtual void onAdPlayableChanged(bool isAdPlayable) = 0;
};
class PluginVungle
{
public:
    static void init(const std::string& appID);
    static void playAd();
    static void playAdIncentivized(const std::string& userID);
    static void clearEventListeners();
    static bool isPlayable();

    static void setListener(VungleListener* listener);
};