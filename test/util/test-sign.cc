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
    bool loop = true;
    while(loop) {
        if(printSign) {
            std::cout << "Test sign";
            for(size_t i = 0; i < inp.size(); i++) {
                std::cout << ' ';
                if(sign[i] > 0) std::cout << ' ';
                std::cout << sign[i];
            }
            std::cout << '\n';
        }

        // Change input sign
        for(size_t i = 0; i < inp.size(); i++) {
            inp[i]->setIsNegative(sign[i] < 0);
        }

        // Call the test function
        func(sign);

        // Move on to the next sign
        size_t index = 0;
        do {
            sign[index] *= -1;
            index++;
            if(index >= inp.size()) {
                loop = false;
                break;
            }
        } while(sign[index - 1] == 1);
    }
}

#define EXPECT_SIGN(__obj__, __sign__) \
    EXPECT_EQ((__obj__)->isNegative(), (__sign__) < 0)
