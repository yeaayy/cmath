
#include <iostream>
#include "cmath/util/pretty-print.hpp"
#include "cmath/parser/expr.hpp"

int main(int argc, const char **argv)
{
    using namespace CMath;
    using namespace CMath::Parser;
    auto expr = XExpression::create();
    expr->getErrorHandler()->addOnError([](ErrorHandler *h) {
        std::cout << "Error: " << h->getMessage() << "\n";
    });

    stream inp(std::cin);
    Object_t result;
    if(!expr->parse(inp, result)) {
        return 1;
    }

    PrettyPrint pp;
    pp.setOutput(stdout);
    pp.print(result);
    std::cout << '\n';
    return 0;
}
