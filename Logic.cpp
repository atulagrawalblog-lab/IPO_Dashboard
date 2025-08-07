#include "Logic.h"
#include <cmath>

std::vector<IPOResult> CalculateIPO(const std::wstring& type, double price, int lotSize) {
    std::vector<IPOResult> results;
    if (price <= 0 || lotSize <= 0) return results;
    double lotValue = price * lotSize;
    const int thresholdSHNI = 200000;
    const int thresholdBHNI = 1000000;

    if (type == L"SME") {
        results.push_back({ L"Retail Individual Investor", 2, 2 * lotSize, 2 * lotValue, L"Fixed allocation for SME IPO retail investors" });
        results.push_back({ L"Small HNI (sHNI)", 3, 3 * lotSize, 3 * lotValue, L"Fixed allocation for SME IPO small HNI investors" });
        int minBHNILots = std::max(3, (int)std::ceil((thresholdBHNI + 1) / lotValue));
        results.push_back({ L"Big HNI (bHNI)", minBHNILots, minBHNILots * lotSize, minBHNILots * lotValue, L"Minimum lots to exceed ₹10,00,000 threshold" });
    } else {
        results.push_back({ L"Retail Individual Investor", 1, 1 * lotSize, 1 * lotValue, L"Fixed allocation for Mainboard IPO retail investors" });
        int minSHNILots = std::max(1, (int)std::ceil((thresholdSHNI + 1) / lotValue));
        results.push_back({ L"Small HNI (sHNI)", minSHNILots, minSHNILots * lotSize, minSHNILots * lotValue, L"Minimum lots to exceed ₹2,00,000 threshold" });
        int minBHNILots = std::max(minSHNILots, (int)std::ceil((thresholdBHNI + 1) / lotValue));
        results.push_back({ L"Big HNI (bHNI)", minBHNILots, minBHNILots * lotSize, minBHNILots * lotValue, L"Minimum lots to exceed ₹10,00,000 threshold" });
    }

    return results;
}
