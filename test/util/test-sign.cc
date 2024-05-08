#include <gtest/gtest.h>

#include <vector>
#include <functional>

#include "cmath/object.hpp"

void test_sign(
    int inputSize,
    CMath::Object_t *input,
    std::vector<int> inputSign,
    std::vector<int> expectSign,
    std::function<void()> func
) {
    for(int i = 0; i < inputSize; i++) {
        input[i]->setIsNegative(inputSign[i] < 0);
    }
    func();
    for(int i = 0; i < inputSize; i++) {
        EXPECT_EQ(input[i]->isNegative(), expectSign[i] < 0) << "At input " << i;
    }
}

void test_sign_full(std::vector<CMath::Object_t> inp, std::function<void(std::vector<int> sign)> func, bool printSign = false)
{
    std::vector<int> sign(inp.size(), 1);
    const int n = 1 << (inp.size());
    for(int j = 0; j < n; j++) {
        // Change input sign
        for(size_t i = 0; i < sign.size(); i++) {
            sign[i] =( (j >> i) & 1) == 1 ? -1 : 1;
            inp[i]->setIsNegative(sign[i] < 0);
        }

        if(printSign) {
            std::cout << "Test sign";
            for(size_t i = 0; i < inp.size(); i++) {
                std::cout << ' ';
                if(sign[i] > 0) std::cout << ' ';
                std::cout << sign[i];
            }
            std::cout << '\n';
        }

        // Call the test function
        func(sign);
    }
}

#define EXPECT_SIGN(__obj__, __sign__) \
    EXPECT_EQ((__obj__)->isNegative(), (__sign__) < 0)
