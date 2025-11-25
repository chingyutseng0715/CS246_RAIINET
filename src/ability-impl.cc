module Ability;

Ability::Ability(std::string name, std::string description, Observer *owner, Board *board)
	: name{name}, description{description}, used{false}, player{owner}, board{board} {}

Ability::~Ability() {}

bool Ability::isUsed() {
	return used;
}

void Ability::markUsed() {
	used = true;
}

std::ostream &operator<<(std::ostream &os, const Ability &ability) {
    os << ability.name << ": " << ability.description;
    return os;
}
