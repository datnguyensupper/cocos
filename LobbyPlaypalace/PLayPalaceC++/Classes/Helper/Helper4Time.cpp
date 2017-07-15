#include "Helper4Time.h"
USING_NS_CC;


string Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(int millisecond) {
	int second = floor(millisecond*1.0 / 1000); // in second
	int hour = floor(second*1.0 / 3600);//in hour
	second -= (hour * 3600);
	int minute = floor(second*1.0 / 60);
	second -= minute * 60;

	//string result = "";
	//string zero = "0";
	//if (hour > 0) {
	//	if (hour < 10) {
	//		result += (zero + ToString(hour));
	//	}
	//}
	CCString * result;
	
	if (hour > 0) {
		result = CCString::createWithFormat("%02i:%02i:%02i", hour, minute, second);
	}
	else {
		result = CCString::createWithFormat("%02i:%02i", minute,second);
	}
	return result->getCString();

}