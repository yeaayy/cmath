#include "cmath/util/expand-bracket.hpp"

#include "cmath/addition.hpp"
#include "cmath/bracket.hpp"
#include "cmath/multiplication.hpp"

namespace CMath {

ExpandBracket::ExpandBracket(bool recursive)
	: recursive(recursive)
{}
bool ExpandBracket::isRecursive()
{
	return recursive;
}
void ExpandBracket::setRecursive(bool recursive)
{
	this->recursive = recursive;
}

void ExpandBracket::expand(Multiplication_t m, size_t childIndex)
{
	auto expanded = std::dynamic_pointer_cast<Addition>(m->get(childIndex));
	auto result = std::make_shared<Addition>();
	m->aborbSignFrom(expanded);
	for(size_t i = 0; i < expanded->getChildCount(); i++) {
		auto term = std::make_shared<Multiplication>();
		for(size_t j = 0; j < m->getChildCount(); j++) {
			if(j == childIndex) {
				// Copy the expanded term
				term->add(expanded->get(i)->copy());
			} else {
				// Otherwise copy similar term
				term->add(m->get(j)->copy());
			}
		}
		term->copySignFrom(m);
		term->aborbSignFrom(expanded->get(i));
		result->add(term);
	}
	// Optionally reset multiplication sign
	m->setIsNegative(false);
	result->visitChild(this);
    m->getParent()->replace(m, result);
}

intptr_t ExpandBracket::onVisit(Multiplication_t m)
{
	if(recursive) {
		Visitor::onVisit(m);
	}
	for(size_t i = 0; i < m->getChildCount(); i++) {
		auto child = m->get(i);
		if(child->is(Type::BRACKET)) {
			auto bracket = std::dynamic_pointer_cast<Bracket>(child);
			auto val = bracket->getValue();
			if(val->is(Type::ADDITION)) {
				m->replace(child, bracket->getValue());
			} else {
				// m->aborbSignFrom(val);
				m->replace(child, bracket->getValue());
				continue;
			}
		} else if(!child->is(Type::ADDITION)) {
			continue;
		}
		expand(m, i);
		return 0;
	}
	return 0;
}

} // namespace CMath
