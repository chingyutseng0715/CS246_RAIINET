module Link;

import <iostream>;
import <compare>;
import Constants;
import Observer;

Link::Link(Observer *player, char symbol, char type, int strength, int move_per_step) :
	player{player}, symbol{symbol}, type{type}, strength{strength},
	move_per_step{move_per_step}, revealed{false}, downloaded{false}, infected{false} {}

std::strong_ordering Link::operator<=>(const Link &other) const {
	if (strength < other.strength) { // Check if the strength of this link is less than other's
		return std::strong_ordering::less;
	} else { // the left one is who initiate the battle and would win if strength are equal
		return std::strong_ordering::greater;
	}
}

void Link::setStrength(int strength) { this->strength = strength; }

void Link::setType(LinkType type) { this->type = type; }

void Link::Boost() { move_per_step += 1; }

void Link::Reveal() { revealed = true; }

void Link::Download() { downloaded = true; }

void Link::Infect() { infected = true; }

Observer * Link::getPlayer() { return player; }

char Link::getSymbol() { return symbol; }

int Link::getStrength() { return strength; }

int Link::getMovePerStep() { return move_per_step; }

bool Link::isVirus() { return type == LinkType::Virus; }

bool Link::isInfected() { return infected; }

bool Link::isRevealed() { return revealed; }

bool Link::isDownloaded() { return downloaded; }

void Link::printLink(std::ostream &os, bool secret) {
	os << symbol << ": ";
	if (revealed || !secret) { // Print the type & strength of the link if it's revealed or not a secret
		os << static_cast<char>(type) << strength;
	} else { // Otherwise, keep the link hidden
		os << UNREVEALED_LINK_CHAR << " ";
	}
	os << "  ";
}
