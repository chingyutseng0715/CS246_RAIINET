module Scan;
import <string>;
import <sstream>;
import Ability;
import Board;
import Link;

Scan::Scan(Observer *owner, Board *board)
	: Ability{"Scan", "Reveals the type and strength of any link on the field", owner, board} {}


void Scan::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	iss >> link_char;
	
	Link* target_link = board->getLink(link_char);
	if (target_link) {
		target_link->setRevealed(true);
	}
}