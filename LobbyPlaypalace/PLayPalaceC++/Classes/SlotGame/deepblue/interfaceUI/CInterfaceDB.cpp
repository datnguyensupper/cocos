#include "CInterfaceDB.h"
#include "Helper/AnimationHelper.h"
#include "SlotGame/base/settings/CSettings.h"

USING_NS_CC;
namespace GameSlot {
	void CInterfaceDB::initFreeSpinIndicator()
	{
		this->oFreeSpinIndicator = new CFreeSpinIndicatorDB();
		this->addChild(oFreeSpinIndicator);
	}

	void CInterfaceDB::onSpinStarted()
	{
		CInterfaceBase::onSpinStarted();
		this->oBubble->start();
	}

	bool CInterfaceDB::init()
	{
		if (!CInterfaceBase::init()) return false;

		this->oBubble = ParticleSystemQuad::create(GameConstant::getInstance()->getResources().mainGame["bubble_particle"]);
		this->oBubble->setPosition(this->oButSpin->getPosition());
		this->oBubble->stop();
		this->addChild(this->oBubble, 200);

		return true;
	}

	CInterfaceDB::CInterfaceDB(CGameBase* oGame):CInterfaceBase(oGame, true)
	{
	}

	CFreeSpinIndicatorDB::CFreeSpinIndicatorDB() : CFreeSpinIndicatorBase()
	{
		//CREATE TEXT UI
		auto createUIElement = [this](int value, const std::string& type) {
			auto oBoxFP = Sprite::createWithSpriteFrameName("box-freespins-bonus");
			oBoxFP->setPosition(-585 * value + value*this->origin.x/2, CSettings::CANVAS_HEIGHT / 2 - 200 + this->origin.x/3);
			this->oContainerRemaining->addChild(oBoxFP);

			auto oTextFS = Sprite::createWithSpriteFrameName(type);
			oTextFS->setPosition(oBoxFP->getPosition() - Vec2(0, 60));
			this->oContainerRemaining->addChild(oTextFS);

			auto oText = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["freespin"], "0");
			oText->setPosition(oBoxFP->getPosition() + Vec2(0, 8));
			this->oContainerRemaining->addChild(oText);

			return oText;
		};

		this->oTextNumberFS = createUIElement(1, "freespins-en");
		this->oTextNumberMulty = createUIElement(-1, "multiplier-en");

		this->hide();
	}
	CFreeSpinIndicatorDB::~CFreeSpinIndicatorDB()
	{

	}
}
