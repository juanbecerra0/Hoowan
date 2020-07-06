#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hoowan/Core/Log.h"
#include "Hoowan/Debug/Instrumentor.h"

#ifdef HW_PLATFORM_WINDOWS
	#include <Windows.h>
#endif