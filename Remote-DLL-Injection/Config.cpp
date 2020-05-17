#include "Config.h"

void Config::GetSetting(char* buffer, const char* appName, const char* key) {

	GetPrivateProfileStringA(appName, key, NULL, buffer, MAX_PATH, path);
}