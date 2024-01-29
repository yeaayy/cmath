#ifndef CMATH_UTIL_PRETTY_PRINT_HPP
#define CMATH_UTIL_PRETTY_PRINT_HPP

#include <vector>

#include "cmath/visitor.hpp"

namespace CMath {

class PrettyPrint : public Visitor
{
public:
    typedef struct {
        int start;
        int end;
    } Offset;

	intptr_t onVisit(Number_t n) override;
	intptr_t onVisit(Variable_t v) override;
	intptr_t onVisit(Function_t f) override;
	intptr_t onVisit(Addition_t a) override;
	intptr_t onVisit(Power_t p) override;
	intptr_t onVisit(Multiplication_t m) override;
	intptr_t onVisit(Fraction_t f)  override;
	intptr_t onVisit(Bracket_t b) override;
	intptr_t onVisit(Relation_t r)  override;
	intptr_t onVisit(Derrivative_t d) override;

	PrettyPrint &highlight(Object_t highlight, const char *highlightStart, const char *highlightEnd);
	PrettyPrint &traceLocation(std::vector<Offset> *offset);
	PrettyPrint &traceList(std::vector<Object_t> *list);
	void setOutput(FILE *output);
	int print(Object_t obj, FILE *out);
	int print(Object_t obj);
	char *toString(Object_t obj, int *length = nullptr);

	PrettyPrint &setSpaceAroundOperator(bool spaceAroundOperator);
	PrettyPrint &setSpaceAroundBracket(bool spaceAroundBracket);
	PrettyPrint &setImplicitMultiplication(bool implicitMultiplication);
	PrettyPrint &setDotNotation(Object_t var);
	bool isSpaceAroundOperator();
	bool isSpaceAroundBracket();
	bool isImplicitMultiplication();
	Object_t getDotNotation();

    friend std::ostream &operator<<(std::ostream &s, Object_t obj);

private:
	void wrap(Object_t, bool, bool, bool);
	void putc(char);
	void putop(const char*, bool, bool);

	Object_t highlighting;
	const char *highlightStart;
	const char *highlightEnd;
	FILE *output = nullptr;
	std::vector<Offset> *offset = nullptr;
	std::vector<Object_t> *list = nullptr;
	int index;
	char lastChar;

	bool spaceAroundOperator = true;
	bool spaceAroundBracket = false;
	bool implicitMultiplication = true;
	Object_t dotNotation = nullptr;
};

} // namespace CMath

#endif /* CMATH_UTIL_PRETTY_PRINT_HPP */
