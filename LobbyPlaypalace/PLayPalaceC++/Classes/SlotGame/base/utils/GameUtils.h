#pragma once
#include "cocos2d.h"

namespace GameSlot {
	class GameUtils
	{
	public:
		/*
		* Split a string by a delimiter
		* @param s: string need to split
		* @param delim: delimiter
		*/
		static std::vector<std::string> splitString(const std::string &s, const char& delim);

		static void centerNode(cocos2d::Node* node, cocos2d::Node* nodeParent = nullptr);
	};
}