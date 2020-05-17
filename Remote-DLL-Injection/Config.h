#pragma once
#include <windows.h>
#include <iostream>

class Config {

public:

	char path[MAX_PATH];

	Config(const char* filename) {

		GetCurrentDirectoryA(MAX_PATH, path);
		strcat_s(path, MAX_PATH, filename);
	}

	void GetSetting(char* buffer, const char* appName, const char* key);
};
