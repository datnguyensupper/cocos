#include "GameConstant.h"

namespace GameSlot {
	static GameConstant* _sharedGameConstant = nullptr;
	GameConstant* GameConstant::getInstance() {
		if (!_sharedGameConstant)
		{
			_sharedGameConstant = new (std::nothrow) GameConstant();
		}
		return _sharedGameConstant;
	}
	void GameConstant::setGame(const std::string& game)
	{
		this->DomainName.gameService.authorization = "https://scmw.spiralworks-cloud.com/lobby-gameplay/gameplay/authorizationByToken";
		this->DomainName.gameService.getBalance = "https://scmw.spiralworks-cloud.com/lobby-gameplay/gameplay/getBalance";
		this->DomainName.gameService.getBet = "https://scmw.spiralworks-cloud.com/lobby-gameplay/gameplay/" + game + "/getBet";
		this->DomainName.gameService.spin = "https://scmw.spiralworks-cloud.com/lobby-gameplay/gameplay/" + game + "/spin";
		this->DomainName.gameService.bonusGame = "https://scmw.spiralworks-cloud.com/lobby-gameplay/gameplay/" + game + "/bonusGame";
	}
	void GameConstant::release()
	{
		CC_SAFE_DELETE(_sharedGameConstant);
	}
}