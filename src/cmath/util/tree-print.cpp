#include "cmath/util/tree-print.hpp"

#include "cmath/all"

namespace CMath {

TreePrint::TreePrint(FILE *dst)
{
	this->dst = dst == nullptr ? stdout : dst;
}

void TreePrint::begin(Object_t o, const char *name, bool hasChild = true)
{
	for(int i = 0; i < (int) marker.size() - 1; i++) {
		switch(marker[i]) {
			case 0: fprintf(dst, "  "); break;
			default: fprintf(dst, " |"); break;
		}
	}
	if(marker.size() > 0) {
		switch(marker[marker.size() - 1]) {
			case 1: fprintf(dst, " `-"); break;
			default: fprintf(dst, " +-"); break;
		}
		marker[marker.size() - 1]--;
	}
	fprintf(dst, "%s%s(%d) %s",
		hasChild ? "-- " : "- ",
		name,
		o->getId(),
		o->isNegative() ? "-" : "");
}

void TreePrint::end(Object_t o)
{
	fputc('\n', dst);
	int itemCount;
	switch(o->getType()) {
	case Type::BRACKET:
		itemCount = 1;
		break;
	case Type::ADDITION:
	case Type::MULTIPLICATION:
		itemCount = std::dynamic_pointer_cast<CommutateOp>(o)->getChildCount();
		break;
	case Type::FUNCTION:
		itemCount = std::dynamic_pointer_cast<Function>(o)->getArgumentCount();
		break;
	default:
		itemCount = 2;
	}
	marker.push_back(itemCount);
	std::dynamic_pointer_cast<Operator>(o)->visitChild(this);
	marker.pop_back();
}

intptr_t TreePrint::onVisit(Number_t n)
{
	begin(n, "Number", false);
	fprintf(dst, " %u\n", n->getValue());
	return 0;
}

intptr_t TreePrint::onVisit(Variable_t v)
{
	begin(v, "Variable", false);
	fprintf(dst, "%s\n", v->getName().c_str());
	return 0;
}

intptr_t TreePrint::onVisit(Function_t f)
{
	begin(f, "Function");
	fprintf(dst, "%s", f->getName().c_str());
	end(f);
	return 0;
}

intptr_t TreePrint::onVisit(Addition_t a)
{
	begin(a, "Addition");
	end(a);
	return 0;
}

intptr_t TreePrint::onVisit(Multiplication_t m)
{
	begin(m, "Multiplication");
	end(m);
	return 0;
}

intptr_t TreePrint::onVisit(Power_t p)
{
	begin(p, "Power");
	end(p);
	return 0;
}

intptr_t TreePrint::onVisit(Fraction_t f)
{
	begin(f, "Fraction");
	end(f);
	return 0;
}

intptr_t TreePrint::onVisit(Bracket_t b)
{
	begin(b, "Bracket");
	end(b);
	return 0;
}

intptr_t TreePrint::onVisit(Derrivative_t d)
{
	begin(d, "Derrivative");
	end(d);
	return 0;
}

} // namespace CMath
