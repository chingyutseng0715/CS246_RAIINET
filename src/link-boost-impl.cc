module LinkBoost;

import <sstream>;
import <string>;
import <stdexcept>;
import Constants;
import Board;
import Ability;
import Link;

LinkBoost::LinkBoost(Observer *owner, Board *board) : 
	Ability{"Link Boost", "Input: <Owned Link> | Desc: Choose to boost one of your links. When boosted, the link moves 2 steps at every turn, with the ability to jump over obstacles", owner, board} {}

void LinkBoost::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Link Boost ability.");
	}
	
	Link* target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player && !target_link->isDownloaded()) {
		target_link->Boost();
        markUsed();
	} else {
		throw std::invalid_argument("Invalid use of Link Boost ability.");
	}
}
