#include "cmath/util/pretty-print.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "cmath/all"
#include "cmath/comparator.hpp"

namespace CMath {

bool operator==(const PrettyPrint::Offset &a, const PrettyPrint::Offset &b)
{
	return a.start == b.start && a.end == b.end;
}

#define BLOCK_START(_x, _sign) \
	if(list != nullptr) list->push_back(_x); \
	PrettyPrint::Offset loc = {index, index}; \
	int el = -1; \
	if(offset) offset->push_back(loc); \
	if(_sign) if(_x->isNegative()) { \
		putop("-", true, false); \
	} \
	if(_x == highlighting) fprintf(output, "%s", highlightStart); \

#define BLOCK_END(_x) \
	if(_x == highlighting) fprintf(output, "%s", highlightEnd); \
	if(el != -1) { \
		(*offset)[el].end = index; \
	} \
	return 0;

namespace {

struct string {
	int size;
	char *str;
};

ssize_t write(struct string *dst, const char *buff, size_t c) {
	dst->str = (char*) realloc(dst->str, dst->size + c + 1);
    std::copy(buff, buff + c, dst->str + dst->size);
	dst->size += c;
	return c;
}

} // namespace

char *PrettyPrint::toString(Object_t obj, int *length)
{
	struct string tmp = {
		.size = 0,
		.str = (char*) malloc(1),
	};
	int len;

#if defined(__ANDROID__)
	len = print(obj, fwopen(&tmp, (int(*)(void*,const char*, int)) write));
#elif  defined(__linux__)
	cookie_io_functions_t funcs = {
		nullptr,
		(ssize_t(*)(void*, const char*, size_t)) write,
		nullptr,
		nullptr,
	};
	len = print(obj, fopencookie(&tmp, "wb", funcs));
#else
#error "Unknown platform"
#endif
	if(length) *length = len;
	fclose(output);
	output = nullptr;
	tmp.str[tmp.size] = '\0';
	return tmp.str;
}

void PrettyPrint::setOutput(FILE *output)
{
	this->output = output;
	index = 0;
}

int PrettyPrint::print(Object_t o)
{
	if(output == nullptr) {
		fprintf(stderr, "error: output is empty. \n");
		return -1;
	}
	index = 0;
    visit(o);
	return index;
}

int PrettyPrint::print(Object_t o, FILE *output)
{
	this->output = output;
	index = 0;
	lastChar = ' ';
    visit(o);
	return index;
}

void PrettyPrint::wrap(Object_t o, bool wrapNegative = false, bool maskOr = false, bool maskAnd = true)
{
	bool wrap = maskAnd && (maskOr || o->getType() < o->getParent()->getType());
	if(wrapNegative) {
		wrap = wrap || o->isNegative();
	}
	if(wrap) {
		putop("{", false, spaceAroundBracket & spaceAroundOperator);
		lastChar = ' ';
        visit(o);
		putop("}", spaceAroundBracket & spaceAroundOperator, false);
	} else {
        visit(o);
	}
}

PrettyPrint &PrettyPrint::setSpaceAroundOperator(bool spaceAroundOperator)
{
	this->spaceAroundOperator = spaceAroundOperator;
	return *this;
}

PrettyPrint &PrettyPrint::setSpaceAroundBracket(bool spaceAroundBracket)
{
	this->spaceAroundBracket = spaceAroundBracket;
	return *this;
}

PrettyPrint &PrettyPrint::setImplicitMultiplication(bool implicitMultiplication)
{
	this->implicitMultiplication = implicitMultiplication;
	return *this;
}

PrettyPrint &PrettyPrint::setDotNotation(Object_t var)
{
	this->dotNotation = var;
	return *this;
}

bool PrettyPrint::isSpaceAroundOperator()
{
	return spaceAroundOperator;
}

bool PrettyPrint::isSpaceAroundBracket()
{
	return spaceAroundBracket;
}

bool PrettyPrint::isImplicitMultiplication()
{
	return implicitMultiplication;
}

Object_t PrettyPrint::getDotNotation()
{
	return dotNotation;
}

void PrettyPrint::putc(char c)
{
	if(lastChar == ' ') {
		if(c == ' ') {
			return;
		}
	}
	if(output != nullptr) {
		fputc(c, output);
	}
	index++;
	lastChar = c;
}

void PrettyPrint::putop(const char *c, bool spaceBefore = true, bool spaceAfter = true)
{
	if(spaceAroundOperator && spaceBefore) {
		putc(' ');
	}
	for(int i = 0; c[i]; i++) {
		putc(c[i]);
	}
	if(spaceAroundOperator && spaceAfter) {
		putc(' ');
	}
}

PrettyPrint &PrettyPrint::highlight(Object_t highlight, const char *highlightStart, const char *highlightEnd)
{
	this->highlighting = highlight;
	this->highlightStart = highlightStart;
	this->highlightEnd = highlightEnd;
	return *this;
}

PrettyPrint &PrettyPrint::traceLocation(std::vector<Offset> *offset)
{
	this->offset = offset;
	return *this;
}

PrettyPrint &PrettyPrint::traceList(std::vector<Object_t> *list) 
{
	this->list = list;
	return *this;
}

intptr_t PrettyPrint::onVisit(Number_t n)
{
	BLOCK_START(n, true)
	if(output != nullptr) {
		fprintf(output, "%d", n->getValue());
	}
	int x = n->getValue();
	do {
		index++;
	} while((x /= 10) > 0);
	lastChar = '1';
	BLOCK_END(n)
}

intptr_t PrettyPrint::onVisit(Variable_t v)
{
	BLOCK_START(v, true)
	if(output != nullptr) {
		fprintf(output, "%s", v->getName().c_str());
	}
	index += v->getName().length();
	lastChar = 'a';
	BLOCK_END(v)
}

intptr_t PrettyPrint::onVisit(Function_t f)
{
	BLOCK_START(f, true)
	if(output != nullptr) {
		fprintf(output, "%s", f->getName().c_str());
	}
	putop("(", false, spaceAroundBracket && spaceAroundOperator);
	lastChar = ' ';
	index += f->getName().length() + 1;
	for(std::size_t i=0; i<f->getArgumentCount(); i++) {
		if(i != 0) {
			putc(',');
			putc(' ');
		}
        visit(f->getArgument(i));
	}
	putop(")", spaceAroundBracket && spaceAroundOperator, false);
	BLOCK_END(f)
}

intptr_t PrettyPrint::onVisit(Addition_t a)
{
	BLOCK_START(a, true)
	for(std::size_t i=0; i<a->getChildCount(); i++) {
		Object_t curr = a->get(i);
		bool isNegative = curr->isNegative();
		curr->setIsNegative(false);
		if(i == 0) {
			if(isNegative) {
				putc('-');
			}
		} else {
			putop(isNegative ? "-" : "+");
		}
        visit(curr);
		curr->setIsNegative(isNegative);
	}
	BLOCK_END(a)
}

intptr_t PrettyPrint::onVisit(Multiplication_t m)
{
	BLOCK_START(m, true)
	for(std::size_t i=0; i<m->getChildCount(); i++) {
		Object_t curr = m->get(i);
		if(i != 0) {
			if(implicitMultiplication) {
				if(lastChar == 'a' || lastChar == '1') {
					putc(' ');
				}
			} else {
				putop("*");
			}
		}
		wrap(curr);
	}
	BLOCK_END(m)
}

intptr_t PrettyPrint::onVisit(Power_t p)
{
	BLOCK_START(p, true)
	wrap(p->getBase(), true);
	putop("^");
	wrap(p->getExponent());
	BLOCK_END(p)
}

intptr_t PrettyPrint::onVisit(Fraction_t f)
{
	BLOCK_START(f, true)
	Object_t a = f->getA();
	wrap(a, true, a->is(Type::FRACTION));
	putop("/");
	wrap(f->getB(), true);
	BLOCK_END(f)
}

intptr_t PrettyPrint::onVisit(Bracket_t b)
{
	BLOCK_START(b, true)
	putop("(", spaceAroundBracket && spaceAroundOperator, spaceAroundBracket & spaceAroundOperator);
	lastChar = ' ';
    visit(b->getValue());
	putop(")", spaceAroundBracket & spaceAroundOperator, spaceAroundBracket && spaceAroundOperator);
	BLOCK_END(b)
}

intptr_t PrettyPrint::onVisit(Relation_t r)
{
	BLOCK_START(r, false)
    visit(r->getA());
	switch(r->getRelationType()) {
		case Relation::Type::EQUAL: putop("="); break;
		case Relation::Type::LESS_THAN: putop("<"); break;
		case Relation::Type::GREATER_THAN: putop(">"); break;
		case Relation::Type::NOT_EQUAL: putop("!="); break;
		case Relation::Type::LESS_THAN_OR_EQUAL: putop("<="); break;
		case Relation::Type::GREATER_THAN_OR_EQUAL: putop(">="); break;
	}
    visit(r->getB());
	BLOCK_END(r)
}

intptr_t PrettyPrint::onVisit(Derrivative_t d)
{
	// TODO: Add more style
	BLOCK_START(d, true)
	if(dotNotation != nullptr) {
		if(Comparator::test(d->getB(), dotNotation) == 0)
		{
			putc('\\');
			for(int i = 0; i < d->getOrder(); i++) {
				putc('d');
			}
			putc('o');
			putc('t');
			wrap(d->getA(), true, false);
		} else {
			goto standardNotation;
		}
	} else {
	standardNotation:
		putc('\\');
		putc('d');
		putc('f');
		if(d->getOrder() > 1) {
			putc('[');
			if(output != nullptr) {
				fprintf(output, "%d", d->getOrder());
			}
			int x = d->getOrder();
			do {
				index++;
			} while((x /= 10) > 0);
			putc(']');
		}
		wrap(d->getA(), true, false);
		wrap(d->getB(), true, false);
	}
	BLOCK_END(d)
}

} // namespace CMath
