#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../Utility/StrManipulation.h"

/// <summary>
/// Parses user input. Should catch some typos from the user.
/// </summary>
std::vector<std::string> ParseFileNames(std::string& names);

/// <summary>
/// Parses user delay input.
/// </summary>
/// <remarks>
/// Delay between each injection.
/// </remarks>
unsigned int ParseDelay(std::string& delay);