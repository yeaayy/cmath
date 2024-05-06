
option(TRACE_OBJECT "Print CMath object creation and destruction" OFF)

add_library(cmath_base STATIC
    config.cpp
    cmath/object.cpp
    cmath/operator.cpp
    cmath/visitor.cpp
    cmath/number.cpp
    cmath/variable.cpp
    cmath/bracket.cpp
    cmath/power.cpp
    cmath/fraction.cpp
    cmath/commutate_op.cpp
    cmath/binary_evaluator.cpp
    cmath/addition.cpp
    cmath/multiplication.cpp
    cmath/comparator.cpp
    cmath/relation.cpp
    cmath/derrivative.cpp
    cmath/function.cpp

    parser/error_handler.cpp
    parser/parser.cpp
    parser/stream.cpp

    cmath/parser/number.cpp
    cmath/parser/whitespace.cpp
    cmath/parser/variable.cpp
    cmath/parser/bracket.cpp
    cmath/parser/expr.cpp

    cmath/util/pretty-print.cpp
    cmath/util/tree-print.cpp
    cmath/util/expand-bracket.cpp
)

if(TRACE_OBJECT)
    target_compile_definitions(cmath_base PRIVATE "TRACE_OBJECT")
endif()

target_include_directories(cmath_base PUBLIC .)

target_sources(cmath PRIVATE main.cpp)

target_link_libraries(cmath PUBLIC cmath_base)
