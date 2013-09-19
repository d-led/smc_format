#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "rlutil.h"

class FormatContext
{
	typedef std::vector<int> TPlaceholders;
	std::string s;
	int pos;
	int last_left_brace;
	int last_key_start;
	int last_value_start;
	static const int START_POS=-1;
	TPlaceholders placeholders;

	static int string_to_key(std::string const& to_parse) {
		int res=START_POS;
		//c++11
		try {
			res=std::stoi(to_parse);
		} catch (std::exception&) {}
		return res;
	}


public:

	void SetString(std::string const& _) { 
		s=_; 
		last_value_start=last_key_start=last_left_brace=pos=START_POS;
		rlutil::setColor(rlutil::WHITE);
	}

	bool End() const {
		bool res=pos >= (static_cast<int>(s.size())-1);
		if (res)
			rlutil::setColor(rlutil::GREY);
		return res;
	}

	char Step() {
		if (End())
			return '\0';

		pos++;
		return s[pos];
	}

	void LeftBrace() {
		last_left_brace=pos;
		last_key_start=last_value_start=START_POS;
		rlutil::setColor(rlutil::BLUE);
	}

	void StartKey() {
		last_key_start=pos;
		last_value_start=START_POS;
		rlutil::setColor(rlutil::YELLOW);
	}

	void AddKeyAndContinue() {
		last_key_start=pos;
		rlutil::setColor(rlutil::WHITE);
	}

	void AddKeyAndStartAddingValue() {
		last_key_start=START_POS;
		last_value_start=pos;
		rlutil::setColor(rlutil::MAGENTA);
	}

	void RightBrace() {
		if (last_left_brace!=START_POS
			&& (pos-last_left_brace) > 1) {
			int start=string_to_key(std::string(s.begin()+last_left_brace+1,s.begin()+pos));
			if (start!=START_POS)
				placeholders.push_back(start);
		}
		last_left_brace=START_POS;
		last_key_start=START_POS;
		last_value_start=START_POS;
		rlutil::setColor(rlutil::LIGHTBLUE);
	}

	void AddValue() {
		last_key_start=pos;
		last_value_start=START_POS;
	}

	void Continue() {
		if (last_value_start>=0)
			rlutil::setColor(rlutil::LIGHTRED);
		else if (last_key_start>=0)
			rlutil::setColor(rlutil::YELLOW);
		else if (last_left_brace>=0)
			rlutil::setColor(rlutil::GREEN);
		else
			rlutil::setColor(rlutil::WHITE);
	}

	void FSMError(const char* a, const char* b) {
		//std::cout<<a<<" "<<b<<std::endl;
	}

	~FormatContext() {
		for (auto k: placeholders) {
			std::cout<<k<<std::endl;
		}
	}
};