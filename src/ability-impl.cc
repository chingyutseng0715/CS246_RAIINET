module Ability;

Ability::Ability(std::string name, std::string description, Observer *owner, Board *board)
	: name{name}, description{description}, used{false}, player{owner}, board{board} {}

bool Ability::isUsed() {
	return used;
}

void Ability::markUsed() {
	used = true;
}

std::string Ability::getName() {
	return name;
}

std::ostream &operator<<(std::ostream &os, const Ability &ability) {
	if (ability.used) os << " (USED)";
	os << " -- " << ability.description;
    return os;
}
