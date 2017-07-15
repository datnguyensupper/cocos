#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum SpinMachineCellType {
	SPRITE,
	LABEL
};
enum SpinMachineSpriteType {
	LOCAL,
	PLIST
};
struct SpinMachineLabelType {
	enum LabelType {
		TTF,
		BMFONT,
	};
	std::string fontName;
	float fontSize;
	LabelType type;
	SpinMachineLabelType(const std::string& fontName, LabelType type, float fontSize) {
		this->fontName = fontName;
		this->type = type;
		this->fontSize = fontSize;
	}
	SpinMachineLabelType() {
		this->fontName = "";
		this->fontSize = 0;
	}
};

class CSpinMachine : public cocos2d::Node{
private:
	int iNumRow;
	int iNumCol;
	float cellWidth;
	float cellHeight;
	float cellSpacingX;
	float cellSpacingY;

	int speed;

	int offsetX;

	float startPos;
	float endPos;

	bool isSpinning;

	int currentMinStep;
	int minStep;

	int currentStopStep;
	int stopStep;

	std::vector<std::string> data;

	std::vector<std::vector<std::string>> replaceData;

	std::vector<std::vector<std::string>> result;

	std::vector<cocos2d::Node*> aCols;

	std::function<void()> onStop;
	std::function<void(int col)> onColStop;

	SpinMachineCellType cellType;
	SpinMachineSpriteType spriteType;
	SpinMachineLabelType labelType;

	int iNextColToStop = -1;
	int iColHasStop = 0;

	cocos2d::Node* createCell(const std::string& data);
	/// <summary>
	/// update cell with data
	/// </summary>
	/// <param name="cell"></param>
	/// <param name="data"></param>
	void updateCell(cocos2d::Node* cell, const std::string& data);
	/// <summary>
	/// create column at index
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	cocos2d::Node* createCol(int index);
	/// <summary>
	/// update value for column
	/// </summary>
	/// <param name="index">index of column</param>
	/// <param name="data">info of column</param>
	/// <param name="bStop">is stop</param>
	void updateCol(int index, const std::vector<std::vector<std::string>>& data, bool bStop);
	std::string generateRandomData();

	void onColReachEnd(int iCol);
	void stopSpin();
public:
	CSpinMachine();
	virtual ~CSpinMachine();
	
	virtual void onEnter();
	/**
	* static function create a spin machine
	* @param type: cell type
	* @param data:cell's data
	*			  vector of string that contains all data;
	*			  if this spin type is Sprite (vector of spriteName or frameName)
	*			  if this spin type is Label (vector of text info)
	* @param iNumRow: number rows
	* @param iNumCol: number cols
	* @param cellWidth: width of cell
	* @param cellHeight: height of cell
	* @param spriteType: sprite type (Plist or Local), ignore if this is Label Cell
	* @param cellSpacingX: spacing X between cell
	* @param cellSpacingY: spacing Y between cell
	*/
	static CSpinMachine* create(
		SpinMachineCellType type,
		const std::vector<std::string>& data,
		int iNumRow, 
		int iNumCol, 
		float cellWidth,
		float cellHeight,
		SpinMachineLabelType labelType,
		SpinMachineSpriteType spriteType = SpinMachineSpriteType::LOCAL,
		float cellSpacingX = 0.0f, 
		float cellSpacingY = 0.0f);

	/**
	* init data
	* @param type: cell type
	* @param data:cell's data
	*			  vector of string that contains all data;
	*			  if this spin type is Sprite (vector of spriteName or frameName)
	*			  if this spin type is Label (vector of text info)
	* @param iNumRow: number rows
	* @param iNumCol: number cols
	* @param cellWidth: width of cell
	* @param cellHeight: height of cell
	* @param spriteType: sprite type, ignore if this is Label Cell
	* @param labelType: label type, ignore if this is Sprite Cell
	* @param cellSpacingX: spacing X between cell
	* @param cellSpacingY: spacing Y between cell
	*/
	bool initWithData(
		SpinMachineCellType type,
		const std::vector<std::string>& data,
		int iNumRow,
		int iNumCol,
		float cellWidth,
		float cellHeight,
		SpinMachineLabelType labelType,
		SpinMachineSpriteType spriteType = SpinMachineSpriteType::LOCAL,
		float cellSpacingX = 0.0f,
		float cellSpacingY = 0.0f);

	/// <summary>
	/// start spin
	/// </summary>
	/// <param name="onColStop">stop event for each column</param>
	/// <param name="onStop">on stop spin</param>
	void startSpin(const std::function<void(int col)>& onColStop = nullptr, const std::function<void()>& onStop = nullptr);
	/// <summary>
	/// update spinning action
	/// </summary>
	/// <param name="dt"></param>
	void spinning(float dt);
	/// <summary>
	/// stop spin
	/// </summary>
	/// <param name="result"></param>
	void stopSpin(const std::vector<std::vector<std::string>>& result);

	/// <summary>
	/// set speed of spinning
	/// </summary>
	/// <param name="speed"></param>
	void setSpeed(int speed) { this->speed = speed; }
	/// <summary>
	/// set min step to stop
	/// </summary>
	/// <param name="step"></param>
	void setMinStepStop(int step) { this->minStep = step; }
	/// <summary>
	/// set step delay between col
	/// </summary>
	/// <param name="step"></param>
	void setStepDelayStopBetweenCol(int step) { this->stopStep = step; }
	/// <summary>
	/// set position of cell
	/// </summary>
	/// <param name="pos"></param>
	void setCellOffsetPos(const cocos2d::Vec2& pos);
	/// <summary>
	/// reset data of spin machine
	/// </summary>
	/// <param name="data"></param>
	void refreshData(const std::vector<std::vector<std::string>>& data);
};