module Ability;

Ability::Ability(std::string name, std::string description, Observer *owner, Board *board)
	: name{name}, description{description}, player{owner}, board{board}, used{false} {}

Ability::~Ability() {}

std::string Ability::getName() const {
    return name;
}

std::ostream &operator<<(std::ostream &os, const Ability &ability) {
    os << ability.name << ": " << ability.description;
    return os;
}