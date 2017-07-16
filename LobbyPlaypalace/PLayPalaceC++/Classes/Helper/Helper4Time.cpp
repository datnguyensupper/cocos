#include "Helper4Time.h"
USING_NS_CC;


string Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(double millisecond) {
	int64_t second = floor(millisecond*1.0 / 1000); // in second
	int day = floor(second*1.0 / 86400);//in hour
	second -= (day * 86400);
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
	std::string result;
	
	if (day > 0) {
		result = StringUtils::format("%i:%02i:%02i:%02i", day, hour, minute, (int)second);
	}else if (hour > 0) {
		result = StringUtils::format("%02i:%02i:%02i", hour, minute, (int)second);
	}
	else {
		result = StringUtils::format("%02i:%02i", minute, (int)second);
	}
	return result;

}

int64_t Helper4Time::getCurrentTimeStamp()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
}
