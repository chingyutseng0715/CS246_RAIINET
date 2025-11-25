module Link;

import <iostream>;
import <compare>;
import Observer;

Link::Link(Observer *player, char symbol, char type, int strength, int move_per_step) :
  player{player}, symbol{symbol}, type{type}, strength{strength},
  move_per_step{move_per_step}, revealed{false}, downloaded{false} {}

std::strong_ordering Link::operator<=>(const Link &other) const {
	if (strength < other.strength) {
		return std::strong_ordering::less;
	} else {
		return std::strong_ordering::greater;
	}
}

void Link::setStrength(int strength) { this->strength = strength; }

void Link::setType(char type) { this->type = type; }

void Link::setMovePerStep(int move_per_step) { this->move_per_step = move_per_step; }

void Link::Reveal() { revealed = true; }

void Link::Download() { downloaded = true; }

Observer* Link::getPlayer() { return player; }

int Link::getStrength() { return strength; }

int Link::getMovePerStep() { return move_per_step; }

bool Link::isVirus() { return type == 'V' || type == 'I'; }

bool Link::isInfected() { return type == 'I'; }

bool Link::isRevealed() { return revealed; }

bool Link::isDownloaded() { return downloaded; }

std::ostream &operator<<(std::ostream &os, const Link &link) {
	os << link.symbol << ": ";
	if (link.revealed) {
		os << link.type << link.strength;
	} else {
		os << "? ";
	}
	os << '\t';
	return os;
}
