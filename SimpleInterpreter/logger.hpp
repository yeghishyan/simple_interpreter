#pragma once
#include <iostream>
#include <string>
#include <vector>

using uint = unsigned int;

class logger {
public:
	logger(std::string line)
		: _line(line) {}
	~logger() = default;

	void push(std::string str, uint pos) {
		std::string out;
		out = _line + "\n";
		
		out.append(pos, ' ');
		out += "^\n";

		out += str;

		_log.push_back(out);
	}

	void print() {
		while (!_log.empty()) {
			std::cout << _log.back()<<std::endl;
			_log.pop_back();
		}
	}

	bool is_empty() {
		return _log.empty();
	}

private:
	std::string _line;
	std::vector<std::string> _log;
};