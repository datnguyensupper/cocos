#include "Helper4String.h"
USING_NS_CC;

struct MatchPathSeparator
{
	bool operator()(char ch) const
	{
		return ch == '/';
	}
};

vector<string> Helper4String::splitString(std::string stringParam, std::string delimiter)
{
	/*std::stringstream test(stringParam);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, key[0]))
	{
		seglist.push_back(segment);
	}
	return seglist;*/

	std::vector<std::string> seglist;
	std::string s = stringParam;
	if (stringParam.empty())
	{
		return seglist;
	}
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		seglist.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	seglist.push_back(s);

	return seglist;
}

std::string Helper4String::getFileNameFromPath(std::string const& pathname)
{
	return std::string(
		std::find_if(pathname.rbegin(), pathname.rend(),
			MatchPathSeparator()).base(),
		pathname.end());
}


cocos2d::CCString* Helper4String::replaceCCString(cocos2d::CCString* cs, const cocos2d::CCString* csearch, const cocos2d::CCString* creplace)
{
	string s = cs->getCString();
	string search = csearch->getCString();
	string replace = creplace->getCString();

	for (size_t pos = 0; ; pos += replace.length()) {
		pos = s.find(search, pos);
		if (pos == string::npos)
			break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}

	return CCString::create(s);
}

std::string Helper4String::upcaseOrLowcaseString(std::string target, int upcase)
{
	if (upcase == 1)
	{
		std::transform(target.begin(), target.end(), target.begin(), ::toupper);
	}
	else
	{
		std::transform(target.begin(), target.end(), target.begin(), ::tolower);
	}
	return target;
}


bool Helper4String::isStringContain(std::string parent, std::string child) {
	if (parent.find(child) != std::string::npos) {
		return true;
	}
	return false;
}


std::string Helper4String::FormatWithCommas(int value) {
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << value;
	return ss.str();
}