#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

/// <summary>
/// Replaces a substring from a string.
/// </summary>
std::string ReplaceAllSubStr(std::string& mainStr, const std::string toBeReplaced, const std::string replaceWith);

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