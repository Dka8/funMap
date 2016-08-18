#pragma once
#ifndef C_Base_H
#define C_Base_H
#include <iostream>
#include <sstream>
#include "ECS_Types.h"

class C_Base {

	friend nlohmann::json& operator >> (nlohmann::json& l_json, C_Base& a) {
		a.readIn(l_json);
		return l_json;
	}
public:
	C_Base(const Component& l_type) : m_type(l_type){}
	virtual ~C_Base(){}
	
	Component getType() { return m_type; }
	virtual void readIn(const nlohmann::json& l_json) = 0;
protected:
	Component		m_type;
};

#endif // !C_Base_H
