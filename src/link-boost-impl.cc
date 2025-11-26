module LinkBoost;
import Board;
import Ability;
import Link;
import <sstream>;
import <string>;
import <stdexcept>;
LinkBoost::LinkBoost(Observer *owner, Board *board)
    : Ability{"Link Boost", "Input: <Link> | Desc: Move 2 steps and also have the ability to jump over obstacles", owner, board} {}

void LinkBoost::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for LinkBoost ability");
	}
	
	Link* target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player) {
		target_link->setMovePerStep(2);
        markUsed();
	}
}