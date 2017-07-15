#include "CInterfaceBO.h"
#include "Helper/AnimationHelper.h"
#include "SlotGame/base/settings/CSettings.h"

USING_NS_CC;
namespace GameSlot {
	void CInterfaceBO::initFreeSpinIndicator()
	{
		this->oFreeSpinIndicator = new CFreeSpinIndicatorBO();
		this->addChild(oFreeSpinIndicator);
	}

	CInterfaceBO::CInterfaceBO(CGameBase* oGame):CInterfaceBase(oGame, true)
	{
	}

	CFreeSpinIndicatorBO::CFreeSpinIndicatorBO() : CFreeSpinIndicatorBase()
	{
		auto createUIElement = [this](int value, const std::string& type) {
			auto oBoxFP = Sprite::createWithSpriteFrameName(type);
			oBoxFP->setPosition(-585 * value + this->origin.x*value, CSettings::CANVAS_HEIGHT / 2 - 165+ this->origin.x/4);
			this->oContainerRemaining->addChild(oBoxFP);

			/*auto oTextFS = Sprite::createWithSpriteFrameName(type);
			oTextFS->setPosition(oBoxFP->getPosition() - Vec2(0, 70));
			this->oContainerRemaining->addChild(oTextFS);*/

			auto oText = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["freespin"], "0");
			oText->setTextColor(Color4B(255,255,0,255));
			oText->setPosition(oBoxFP->getPosition() + Vec2(0, -16));
			this->oContainerRemaining->addChild(oText);

			return oText;
		};

		this->oTextNumberFS = createUIElement(1, "freespins-box");
		this->oTextNumberMulty = createUIElement(-1, "multiplier-box");

		this->hide();
	}
	CFreeSpinIndicatorBO::~CFreeSpinIndicatorBO()
	{

	}
}
