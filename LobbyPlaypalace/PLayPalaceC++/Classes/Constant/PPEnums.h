#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-27
* file: PPEnums.h
*/
namespace ppEnum
{
	enum GameSlotOrderId
	{
		NEZHA = 40,
		GOLDEN_EGGS = 41,
		PHARAOH = 42,
		BOXING = 43,
		ROMAN_EMPIRE = 44,
		CANDYLICIOUS = 45,
		FRUITILICIOUS = 46,
		KPOP = 47,
		LITTLE_MONSTERS = 48,
		MAFIA = 49,
		SHERLOCK = 50,
		MAGIC_QUEST = 51,
		BIKINI_BEACH = 52,
		FOUR_BEAUTIES = 53,
		ZEUS = 54,
		DEEP_BLUE = 55,
	};
	enum PPCurrency
	{
		COIN_CURRENCY,
		CROWN_CURRENCY
	};
	enum GameScene
	{
		InitSession = 1,
		Lobby = 2,
		Login = 3,
		LuckyWheel = 4,
		GameSlot = 5
	};
	enum LoginAndInitSSFrom
	{
		Facebook,
		PPAccount,
		Guess
	};
}