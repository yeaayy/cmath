#include "cmath/visitor.hpp"

#include "cmath/all"
#include <exception>

namespace CMath {

intptr_t Visitor::onVisit(Number_t f)
{
    return 0;
}

intptr_t Visitor::onVisit(Variable_t a)
{
    return 0;
}

intptr_t Visitor::onVisit(Function_t f)
{
    f->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Addition_t a)
{
    a->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Power_t p)
{
    p->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Multiplication_t m)
{
    m->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Fraction_t f)
{
    f->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Bracket_t b)
{
    b->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Relation_t r)
{
    r->visitChild(this);
    return 0;
}

intptr_t Visitor::onVisit(Derrivative_t d)
{
    return 0;
}

intptr_t Visitor::visit(Object_t o)
{
    switch(o->getType()) {
        case Type::ADDITION: return onVisit(std::static_pointer_cast<Addition>(o));
        case Type::MULTIPLICATION: return onVisit(std::static_pointer_cast<Multiplication>(o));
        case Type::FRACTION: return onVisit(std::static_pointer_cast<Fraction>(o));
        case Type::POWER: return onVisit(std::static_pointer_cast<Power>(o));
        case Type::BRACKET: return onVisit(std::static_pointer_cast<Bracket>(o));
        case Type::RELATION: return onVisit(std::static_pointer_cast<Relation>(o));
        case Type::NUMBER: return onVisit(std::static_pointer_cast<Number>(o));
        case Type::VARIABLE: return onVisit(std::static_pointer_cast<Variable>(o));
        case Type::FUNCTION: return onVisit(std::static_pointer_cast<Function>(o));
        case Type::DERRIVATIVE: return onVisit(std::static_pointer_cast<Derrivative>(o));
        default: throw std::exception();
    }
}

} // namespace CMath

