#pragma once
#include "cocos2d.h"

#include "../constant/GameConstant.h"
#include "../settings/CSettings.h"

namespace GameSlot {
	struct ObjectWinPosition
	{
		std::string id;
		int line;
		double win;
		int mul;
		std::string pos;
		bool isBonus;

		ObjectWinPosition(int line,
			double win,
			int mul,
			const std::string& pos,
			bool isBonus) {
			this->line = line;
			this->win = win;
			this->mul = mul;
			this->pos = pos;
			this->isBonus = isBonus;
			this->id = ToString(this->line) + "_" +
				ToString(this->mul) + "_" +
				this->pos;
		}
	};
	struct ObjectTableWin
	{
		int card;
		int count;
		int wild;

		ObjectTableWin(int card,
			int count,
			int wild) {
			this->card = card;
			this->count = count;
			this->wild = wild;
		}
	};

	struct ObjectCell
	{
		int row;
		int col;

		ObjectCell(int row, int col) {
			this->row = row;
			this->col = col;
		}
	};

	struct ObjectWinningLine
	{
		int line;
		int amount;
		bool isBonus;
		std::vector<ObjectCell> list;
		int value;
		int colAnim;

		ObjectWinningLine(int line,
			int amount,
			bool isBonus,
			const std::vector<ObjectCell>& list,
			int value,
			int colAnim) {
			this->line = line;
			this->amount = amount;
			this->list = list;
			this->isBonus = isBonus;
			this->value = value;
			this->colAnim = colAnim;
		}
	};

	struct ObjectBonus
	{
		int select;
		double win;
		double bet;
		double win_pot;
		int type;

		ObjectBonus() {
			this->select = this->win = this->bet = this->type = 0;
		}
		ObjectBonus(int select,
			double win,
			int type) {
			this->select = select;
			this->win = win;
			this->type = type;
		}

		ObjectBonus(int select,
			double win,
			double bet,
			double win_pot,
			int type) {
			this->select = select;
			this->win = win;
			this->bet = bet;
			this->win_pot = win_pot;
			this->type = type;
		}
	};
	struct ObjectAdditionInfo
	{
	};
	struct ObjectBonusRestore
	{
		int bonus_id;
		int bonus_step;
		int counter;
		int multiplier;
		double win;
		ObjectAdditionInfo* oInfo = nullptr;
		bool finish;
		std::vector<ObjectBonus> history;

		~ObjectBonusRestore() {
			CC_SAFE_DELETE(oInfo);
		}
	};
	struct ObjectMagicItemReceiveAfterSpin
	{
		int magicItemType;
		int ** aLuckySymbolWheels; //lucky symbol

		~ObjectMagicItemReceiveAfterSpin() {
			if (aLuckySymbolWheels != nullptr) {
				for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
					CC_SAFE_DELETE_ARRAY(this->aLuckySymbolWheels[i]);
				}
				CC_SAFE_DELETE_ARRAY(this->aLuckySymbolWheels);
			}
		}
	};
}
