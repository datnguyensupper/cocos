#pragma once

#include "cocos2d.h"
#include "PluginVungle.h"

class PluginVungleController : public VungleListener
{
private:
    std::function<void(bool isSuccess)> callbackEnd;
    std::function<void()> callbackStart;
public:
    PluginVungleController();

    void init();
    void playAd(const std::function<void(bool isSuccess)>& callbackEnd, const std::function<void()>& callbackStart = nullptr);
    bool isAdPlayable() { return PluginVungle::isPlayable(); }

    virtual void onAdStart() override;
    virtual void onAdUnavailable(const std::string &reason) override;
    virtual void onAdEnd(bool wasSuccessfulView) override;
    virtual void onAdPlayableChanged(bool isAdPlayable) override;
};