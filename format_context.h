#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>

#ifdef DO_DEMO
#include "rlutil.h"
#endif

typedef std::map<std::string,std::string> TKeyValueMap;

struct TConfig {
	static const char scope_begin='{';
	static const char scope_end='}';
	static const char separator=',';
	static const char equals='=';
	static const size_t index_begin=1;
	static int string_to_key(std::string const& to_parse) {
		int res=-1;
		std::istringstream ss(to_parse);
		ss.imbue(std::locale::classic());
		ss >> res;
		if (!ss.fail() && ss.eof())
			return res;
		return -1;
	}
};

///BEGIN FORMAT CONTEXT///

static const int START_POS=-1;

struct Placeholder {
	int id;
	int length;
	TKeyValueMap config;
	Placeholder():id(START_POS),length(START_POS){}
};

typedef std::vector< std::pair<int,Placeholder> > Placeholders;

class FormatContext
{
	struct ParserState {
		std::string format_string;
		int pos;
		int last_left_brace;
		int last_key_start;
		int last_value_start;
		std::string last_key;
		Placeholder current_placeholder;
		Placeholders placeholders;
	} state;

public:

	bool IsAtEnd() const {
		bool res=state.pos >= (static_cast<int>(state.format_string.size())-1);
#ifdef DO_DEMO
		if (res)
			rlutil::setColor(rlutil::GREY);
#endif
		return res;
	}

	char Step() {
		if (IsAtEnd())
			return '\0';

		state.pos++;
		return state.format_string[state.pos];
	}

	void ResetPlaceholderState() {
		state.last_value_start=state.last_key_start=state.last_left_brace=START_POS;
	}
	
	void SetString(std::string const& _) { 
		state.format_string=_;
		state.pos=START_POS;
		ResetPlaceholderState();
#ifdef DO_DEMO
		rlutil::setColor(rlutil::WHITE);
#endif
	}

	void TryAddPlaceholder() {
		if (state.current_placeholder.id!=START_POS) {
			state.current_placeholder.length=state.pos-state.last_left_brace+1;
			state.placeholders.push_back(std::make_pair(state.last_left_brace,state.current_placeholder));
		}
	}

public:


	void StartCollectingPlaceholder() {
		state.current_placeholder=Placeholder();
		state.last_left_brace=state.pos;
		state.last_key_start=state.last_value_start=START_POS;
		state.last_key="";
#ifdef DO_DEMO
		rlutil::setColor(rlutil::BLUE);
#endif
	}

	void ParsePlaceholder() {
		int id=TConfig::string_to_key(std::string(state.format_string.begin()+state.last_left_brace+1,state.format_string.begin()+state.pos));
		state.current_placeholder.id=id;
	}

	void AddValue() {
		state.current_placeholder.config[state.last_key]=
			std::string(state.format_string.begin()+state.last_value_start+1,state.format_string.begin()+state.pos);
		state.last_key_start=state.pos;
		state.last_value_start=START_POS;
	}

	void StartKey() {
		state.last_key_start=state.pos;
		state.last_value_start=START_POS;
		state.last_key="";
#ifdef DO_DEMO
		rlutil::setColor(rlutil::YELLOW);
#endif
	}

	void AddKey() {
		if ( (state.pos-state.last_key_start) < 1 )
			return;
		state.last_key=std::string(state.format_string.begin()+state.last_key_start+1,state.format_string.begin()+state.pos);
		state.current_placeholder.config[state.last_key]="";
	}

	void ContinueCollectingKeys() {
		state.last_key_start=state.pos;
#ifdef DO_DEMO
		rlutil::setColor(rlutil::WHITE);
#endif
	}

	void StartAddingValue() {
		state.last_key_start=START_POS;
		state.last_value_start=state.pos;
#ifdef DO_DEMO
		rlutil::setColor(rlutil::MAGENTA);
#endif
	}

	void FinishCollectingPlaceholder() {
		if (state.last_key_start!=START_POS)
			AddKey();

		if (state.last_left_brace!=START_POS
			&& (state.pos-state.last_left_brace) > 1) {
				TryAddPlaceholder();
		}

		ResetPlaceholderState();
#ifdef DO_DEMO
		rlutil::setColor(rlutil::LIGHTBLUE);
#endif
	}

	void Continue() {
#ifdef DO_DEMO
		if (state.last_value_start>=0)
			rlutil::setColor(rlutil::LIGHTRED);
		else if (state.last_key_start>=0)
			rlutil::setColor(rlutil::YELLOW);
		else if (state.last_left_brace>=0)
			rlutil::setColor(rlutil::GREEN);
		else
			rlutil::setColor(rlutil::WHITE);
#endif
	}

	void FSMError(const char*, const char*) {
	}

	Placeholders Get() {
		return state.placeholders;
	}

#ifdef DO_DEMO
	~FormatContext() {
		for (auto k: state.placeholders) {
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
#endif

};

///END FORMAT CONTEXT///
