#pragma once
#ifndef Observer_H
#define Observer_H
#include "Message.h"

class Observer {
public:
	virtual ~Observer() {}
	virtual void Notify(const Message &l_message) = 0;
};

#endif // !Observer_H

