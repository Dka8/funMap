#pragma once
#ifndef MessageHandler_H
#define MessageHandler_H
#include "Communicator.h"
#include "EntityMessages.h"
#include <unordered_map>

using Subscribtions = std::unordered_map<EntityMessage, Communicator>;

class MessageHandler {
public:
	bool Subscribe(const EntityMessage &l_type, Observer *l_obsever) {
		return m_communicators[l_type].AddObserver(l_obsever);
	}
	bool Unsubscribe(const EntityMessage &l_type, Observer *l_obsever) {
		return m_communicators[l_type].RemoveObserver(l_obsever);
	}
	void Dispatch(const Message &l_msg) {
		auto itr = m_communicators.find((EntityMessage)l_msg.m_type);
		if (itr == m_communicators.end()) { return; }
		itr->second.Broadcast(l_msg);
	}

private:
	Subscribtions	m_communicators;
};

#endif // !MessageHandler_H

