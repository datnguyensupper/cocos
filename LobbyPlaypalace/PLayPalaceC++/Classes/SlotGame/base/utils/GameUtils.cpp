#include "GameUtils.h"
#include "../settings/CSettings.h"

namespace GameSlot {
	std::vector<std::string> GameUtils::splitString(const std::string & s, const char & delim)
	{
		std::vector<std::string> elems;
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	void GameUtils::centerNode(cocos2d::Node* node, cocos2d::Node* nodeParent) {
		auto visibleSize = nodeParent ? nodeParent->getContentSize() :
			cocos2d::Size(CSettings::CANVAS_WIDTH, CSettings::CANVAS_HEIGHT);
		auto origin = nodeParent ? nodeParent->getPosition() :
			cocos2d::Vec2::ZERO;
		node->setPosition(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2);
	}
}