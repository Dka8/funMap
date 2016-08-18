#pragma once
#ifndef ECS_Types_H
#define ECS_Types_H
#define _USE_MATH_DEFINES
#include "ATLComTime.h"
#include "json.hpp"

const unsigned int MaskLength = 2;

using ComponentType = unsigned int;
#define N_COMPONENT_TYPES 2;

enum class Component {
	Drawable, Position
};

enum class System {
	Renderer = 0, Position
};

#endif // !ECS_Types_H