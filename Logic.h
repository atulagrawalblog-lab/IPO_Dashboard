#pragma once
#include <string>
#include <vector>
struct IPOResult {
    std::wstring category;
    int lots;
    int shares;
    double amount;
    std::wstring description;
};
std::vector<IPOResult> CalculateIPO(const std::wstring& type, double price, int lotSize);
