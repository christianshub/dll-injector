#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

std::string ReplaceAllSubStr(std::string& mainStr, const std::string toBeReplaced, const std::string replaceWith);

std::vector<std::string> ParseFileNames(std::string& names);
unsigned int ParseDelay(std::string& delay);