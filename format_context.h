#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "rlutil.h"

class FormatContext
{
	static const int START_POS=-1;
	struct Placeholder {
		int id;
		int length;
		std::map<std::string,std::string> config;
		Placeholder():id(START_POS),length(START_POS){}
	};
	typedef std::vector< std::pair<int,Placeholder> > TPlaceholders;
	std::string s;
	int pos;
	int last_left_brace;
	int last_key_start;
	int last_value_start;
	std::string last_key;
	Placeholder current_placeholder;
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
		current_placeholder=Placeholder();
		last_left_brace=pos;
		last_key_start=last_value_start=START_POS;
		last_key="";
		rlutil::setColor(rlutil::BLUE);
	}

	void ParsePlaceholder() {
		int id=string_to_key(std::string(s.begin()+last_left_brace+1,s.begin()+pos));
		current_placeholder.id=id;
	}

	void StartKey() {
		last_key_start=pos;
		last_value_start=START_POS;
		last_key="";
		rlutil::setColor(rlutil::YELLOW);
	}

	void AddKey() {
		if ( (pos-last_key_start) < 1 )
			return;
		last_key=std::string(s.begin()+last_key_start+1,s.begin()+pos);
		current_placeholder.config[last_key]="";
	}

	void AddKeyAndContinue() {
		AddKey();
		last_key_start=pos;
		rlutil::setColor(rlutil::WHITE);
	}

	void AddKeyAndStartAddingValue() {
		AddKey();
		last_key_start=START_POS;
		last_value_start=pos;
		rlutil::setColor(rlutil::MAGENTA);
	}

	void RightBrace() {
		if (last_key_start!=START_POS)
			AddKey();

		if (last_left_brace!=START_POS
			&& (pos-last_left_brace) > 1) {

				if (current_placeholder.id!=START_POS) {
					current_placeholder.length=pos-last_left_brace+1;
					placeholders.push_back(std::make_pair(last_left_brace,current_placeholder));
				}
		}
		last_left_brace=START_POS;
		last_key_start=START_POS;
		last_value_start=START_POS;
		rlutil::setColor(rlutil::LIGHTBLUE);
	}

	void AddValue() {
		current_placeholder.config[last_key]=
			std::string(s.begin()+last_value_start+1,s.begin()+pos);
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
			std::cout<<k.first<<"-"<<k.first+k.second.length-1<<": "<<k.second.id<<" ";
			for (auto v: k.second.config) {
				std::cout<<v.first;
				if (v.second.length())
					std::cout<<"="<<v.second;
				std::cout<<" ";
			}
			std::cout<<std::endl;
		}
	}
};
