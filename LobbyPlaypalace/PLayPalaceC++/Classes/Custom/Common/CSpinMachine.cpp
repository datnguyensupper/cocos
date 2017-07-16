#include "CSpinMachine.h"
#include "Manager/DeviceManager.h"

USING_NS_CC;
using namespace std;

CSpinMachine::CSpinMachine() : Node(),
isSpinning(false),
speed(3000),
minStep(0),
stopStep(0)
{
}

CSpinMachine::~CSpinMachine()
{
}

CSpinMachine * CSpinMachine::create(
	SpinMachineCellType type,
	const std::vector<std::string>& data,
	int iNumRow,
	int iNumCol,
	float cellWidth,
	float cellHeight,
	SpinMachineLabelType labelType,
	SpinMachineSpriteType spriteType,
	float cellSpacingX,
	float cellSpacingY)
{
	CSpinMachine* spinMachine = new CSpinMachine();

	if (spinMachine->initWithData(
		type,
		data,
		iNumRow,
		iNumCol,
		cellWidth,
		cellHeight,
		labelType,
		spriteType,
		cellSpacingX,
		cellSpacingY))
	{
		spinMachine->autorelease();

		return spinMachine;
	}
	CC_SAFE_DELETE(spinMachine);
	return NULL;
}

bool CSpinMachine::initWithData(
	SpinMachineCellType type,
	const std::vector<std::string>& data,
	int iNumRow,
	int iNumCol,
	float cellWidth,
	float cellHeight,
	SpinMachineLabelType lbType,
	SpinMachineSpriteType sprType,
	float cellSpacingX,
	float cellSpacingY)
{
	this->data = data;
	this->cellType = type;
	this->spriteType = sprType;
	this->labelType = lbType;

	this->iNumRow = iNumRow;
	this->iNumCol = iNumCol;
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;
	this->cellSpacingX = cellSpacingX;
	this->cellSpacingY = cellSpacingY;

	this->startPos = iNumRow * (this->cellHeight + this->cellSpacingY);
	this->endPos = -iNumRow * (this->cellHeight + this->cellSpacingY);

	this->offsetX = this->iNumRow;

	this->replaceData.resize(iNumCol);

	this->setContentSize(Size(this->iNumCol * this->cellWidth + (this->iNumCol - 1) * this->cellSpacingX,
		this->iNumRow * this->cellHeight + (this->iNumRow - 1) * this->cellSpacingY));

	auto stencil = DrawNode::create();
	stencil->drawSolidRect(
		Point(-this->cellWidth / 2, -this->cellHeight / 2),
		Point(-this->cellWidth / 2 + this->getContentSize().width,
			this->cellHeight / 2),
		Color4F(0, 0, 0, 0));

	auto clipNode = ClippingNode::create();
	clipNode->setStencil(stencil);
	this->addChild(clipNode);
	clipNode->setCascadeOpacityEnabled(true);

	for (int i = 0; i < iNumCol; ++i) {
		auto col = this->createCol(i);
		if (col == nullptr) {
			return false;
		}
		else {
			col->setCascadeOpacityEnabled(true);
			clipNode->addChild(col);
			aCols.push_back(col);
		}
	}

	this->setCascadeOpacityEnabled(true);
    return true;
}

cocos2d::Node * CSpinMachine::createCell(const std::string& data)
{
	Node* cell = NULL;
	switch (this->cellType)
	{
	case SPRITE:
		switch (this->spriteType)
		{
		case SpinMachineSpriteType::LOCAL:
			cell = Sprite::create(data);
			break;
		case SpinMachineSpriteType::PLIST:
			cell = Sprite::createWithSpriteFrameName(data);
			break;
		default:
			break;
		}
		break;
	case LABEL:
		switch (this->labelType.type)
		{
		case SpinMachineLabelType::TTF:
			cell = Label::createWithTTF(data, this->labelType.fontName, this->labelType.fontSize);
			break;
		case SpinMachineLabelType::BMFONT:
			cell = Label::createWithBMFont(this->labelType.fontName, data);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			if (DeviceManager::getInstance()->isLowRamDevice()) {
				cell->setScale(0.8f);
			}
#endif

			
			break;
		}
		break;
	default:
		break;
	}
	if (cell != NULL) {
		cell->setContentSize(Size(this->cellWidth, this->cellHeight));
	}
	return cell;
}

void CSpinMachine::updateCell(cocos2d::Node* cell, const std::string& data)
{
	switch (this->cellType)
	{
	case SPRITE:
		switch (this->spriteType)
		{
		case SpinMachineSpriteType::LOCAL:
			((Sprite*)cell)->setTexture(data);
			break;
		case SpinMachineSpriteType::PLIST:
			((Sprite*)cell)->setSpriteFrame(data);
			break;
		default:
			break;
		}
		break;
	case LABEL:
		switch (this->labelType.type)
		{
		case SpinMachineLabelType::TTF:
		case SpinMachineLabelType::BMFONT:
			((Label*)cell)->setString(data);
			break;
		}
		break;
	default:
		break;
	}
}

cocos2d::Node* CSpinMachine::createCol(int index)
{
	Node* col = Node::create();
	col->setPositionX(index * (this->cellWidth + this->cellSpacingX));

	//create main cells
	for (int i = 0; i < iNumRow; ++i) {
		auto cell = this->createCell(this->generateRandomData());
		if (cell == nullptr) {
			return nullptr;
		}
		else {
			cell->setPositionY(i * (this->cellHeight + this->cellSpacingY));
			col->addChild(cell);
		}

		//cell at top
		string data = this->generateRandomData();
		this->replaceData[index].push_back(data);
		cell = this->createCell(data);
		if (cell == nullptr) {
			return nullptr;
		}
		else {
			cell->setPositionY((i + iNumRow) * (this->cellHeight + this->cellSpacingY));
			col->addChild(cell);
		}

		//cell at bottom
		cell = this->createCell(data);
		if (cell == nullptr) {
			return nullptr;
		}
		else {
			cell->setPositionY((i - iNumRow) * (this->cellHeight + this->cellSpacingY));
			col->addChild(cell);
		}
	}

	return col;
}

void CSpinMachine::updateCol(int iCol, const std::vector<std::vector<std::string>>& data, bool bStop)
{
	if (!bStop) {
		for (int i = 2; i < this->iNumRow * 3; i += 3) {
			this->updateCell(this->aCols[iCol]->getChildren().at(i), this->replaceData[iCol][i - 2]);
		}
		this->replaceData[iCol].clear();
	}

	for (int i = 0, j = 0; i < this->iNumRow * 3; i += 3, ++j) {
		this->updateCell(this->aCols[iCol]->getChildren().at(i), data[iCol][j]);

		if (!bStop) {
			string data = this->generateRandomData();
			this->replaceData[iCol].push_back(data);
			this->updateCell(this->aCols[iCol]->getChildren().at(i + 1), data);
		}
	}
}

std::string CSpinMachine::generateRandomData()
{
	return this->data.size() > 0 ? this->data[RandomHelper::random_int(0, (int)this->data.size() - 1)] : "";
}

void CSpinMachine::onColReachEnd(int iCol)
{
	if (this->iNextColToStop == iCol) {
		this->aCols[iCol]->setPositionY(0);
	}
	else {
		this->updateCol(iCol, { {this->generateRandomData()}, {this->generateRandomData()}, {this->generateRandomData()} }, false);
		this->aCols[iCol]->setPositionY(this->startPos);
	}
}

void CSpinMachine::startSpin(const std::function<void(int col)>& onColStop, const std::function<void()>& onStop)
{
	if (this->isSpinning) return;

	this->result.clear();
	this->iNextColToStop = -1;
	this->iColHasStop = 0;
	this->currentMinStep = 0;
	this->currentStopStep = 0;
	this->startPos = iNumRow * (this->cellHeight + this->cellSpacingY);
	this->endPos = -iNumRow * (this->cellHeight + this->cellSpacingY);
	this->isSpinning = true;

	this->onColStop = onColStop;
	this->onStop = onStop;

	for (int iCol = 0, size = this->aCols.size(); iCol < size; ++iCol) {
		for (int i = 0, j = 0; i < this->iNumRow * 3; i += 3, ++j) {
			this->updateCell(this->aCols[iCol]->getChildren().at(i + 1), this->replaceData[iCol][j]);
			this->updateCell(this->aCols[iCol]->getChildren().at(i + 2), this->replaceData[iCol][j]);
		}
	}

	this->schedule(schedule_selector(CSpinMachine::spinning));
}

void CSpinMachine::spinning(float dt)
{
	if (this->iColHasStop == this->iNumCol) this->stopSpin();

	auto prepareToStop = false;
	for (int i = iColHasStop, size = this->aCols.size(); i < size; ++i) {
		if (i == this->iNextColToStop && 
			this->aCols[i]->getPositionY() <= 0) {
			this->onColReachEnd(i);
			this->iColHasStop++;
		}
		else {
			if (this->aCols[i]->getPositionY() <= this->endPos) {
				this->onColReachEnd(i);
				prepareToStop = true;
			}
			this->aCols[i]->setPositionY(this->aCols[i]->getPositionY() - speed * dt);
		}
	}
	if (prepareToStop && !this->result.empty() && (this->iNextColToStop < (int)this->aCols.size()) &&
		this->currentMinStep >= this->minStep &&
		this->currentStopStep >= this->stopStep) {
		this->currentStopStep = 0;
		this->iNextColToStop++;
		this->updateCol(this->iNextColToStop, this->result, true);
		if (this->onColStop) {
			this->onColStop(this->iNextColToStop);
		}
	}
	else {
		this->currentMinStep++;
		this->currentStopStep++;
	}
}

void CSpinMachine::stopSpin()
{
	this->unschedule(schedule_selector(CSpinMachine::spinning));
	this->isSpinning = false;
	for (auto col : this->aCols) {
		col->setPositionY(0);
	}

	if (this->onStop) {
		this->onStop();
	}
}

void CSpinMachine::stopSpin(const std::vector<std::vector<std::string>>& result)
{
	this->result = result;
}

void CSpinMachine::setCellOffsetPos(const cocos2d::Vec2 & pos)
{
	for (auto col : this->aCols) {
		for (auto cell : col->getChildren()) {
			cell->setPosition(cell->getPosition() + pos);
		}
	}
}

void CSpinMachine::refreshData(const std::vector<std::vector<std::string>>& data)
{
	for (int iCol = 0, size = this->aCols.size(); iCol < size; ++iCol) {
		this->updateCol(iCol, data, false);
	}
}


void CSpinMachine::onEnter()
{
	Node::onEnter();
	this->stopSpin();
}
