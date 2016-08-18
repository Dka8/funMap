#pragma once
#ifndef ECS_Types_H
#define ECS_Types_H
#define _USE_MATH_DEFINES
#include "ATLComTime.h"
#include "json.hpp"

const unsigned int MaskLength = 3;

using ComponentType = unsigned int;
#define N_COMPONENT_TYPES 3;

enum class Component {
	Drawable, Position, Plantable
};

enum class System {
	Renderer = 0, Planting
};

#endif // !ECS_Types_H