#pragma once

#include <vector>
#include "Vec2.h"

struct IndexedLineList
{
	std::vector<Vec2> vertices;
	std::vector<size_t> indices;
};