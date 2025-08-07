#pragma once
#include <string>

void SaveSetting(const std::wstring& key, const std::wstring& value);
std::wstring LoadSetting(const std::wstring& key, const std::wstring& def);
