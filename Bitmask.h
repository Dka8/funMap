#pragma once
#ifndef Intmask_H
#define Intmask_H
#include <array>
#include <iostream>
#include <sstream>
#include "ECS_Types.h"
#include "json.hpp"

using Bitset = std::array<unsigned int, MaskLength>;

class Bitmask {
	friend std::ostream& operator<< (std::ostream& cout, const Bitmask& l_bitmask) {
		Bitset &set = l_bitmask.GetMask();
		for (auto &itr : set) {
			cout << itr;
		}
		return cout;
	}

	friend std::istream& operator>> (std::istream& cin, Bitmask& l_bitmask) {
		std::string line;
		cin >> line;
		l_bitmask.SetMask(line);
		return cin;
	}
	friend std::stringstream& operator>> (std::stringstream& cin, Bitmask& l_bitmask) {
		std::string line;
		cin >> line;
		l_bitmask.SetMask(line);
		return cin;
	}
	friend nlohmann::json& operator >> (nlohmann::json& json, Bitmask& l_bitmask) {
		std::string line = json["mask"].get<std::string>();
		l_bitmask.SetMask(line);
		return json;
	}

public:
	Bitmask() {
		Clear();
	}
	Bitmask(const Bitset &l_ints) {
		SetMask(l_ints);
	}
	Bitset GetMask() const{ return m_ints; }

	void SetMask(const Bitset &l_ints) {
		for (auto &itr : l_ints) {
			if ((itr == 0) || (itr == 1)) {
				continue;
			}
			else {
				std::cout << "Wrong intmask\n";
				return;
			}
		}
		m_ints = l_ints;
	}
	void SetMask(const std::string &l_line) {
		Clear();
		auto s = m_ints.begin();
		for (auto itr = l_line.begin(); itr != l_line.end(); ++itr) {
			if (*itr == '1') { *s = 1; }
			++s;
			if (s == m_ints.end()) { break; }
		}
	}
	static bool Matches(const Bitmask &l_ints, const Bitset &l_relevant) {
		auto one = l_ints.GetMask().begin();
		for (auto &itr : l_relevant) {
			//std::cout << itr << " " << *one<< std::endl;
			if (itr == 1) {
				if ((*one) != 1) { return false; }
			}
			else { ++one; continue; }
			++one;
		}
		return true;
	}
	bool GetBit(const unsigned int l_pos)const {
		return m_ints[l_pos];
	}
	void TurnOnBit(const unsigned int l_pos) {
		m_ints[l_pos] = 1;
	}
	void ClearBit(const unsigned int l_pos) {
		m_ints[l_pos] = 0;
	}
	void ToggleBit(const unsigned int l_pos) {
		if (m_ints[l_pos] == 0) { m_ints[l_pos] = 1; }
		else if (m_ints[l_pos] == 1) { m_ints[l_pos] = 0; }
	}
	void Clear(){
		for (auto &itr : m_ints) { itr = 0; }
	}

private:
	Bitset		m_ints;
};

#endif // !Intmask_H

