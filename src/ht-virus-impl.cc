module HTVirus;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

HTVirus::HTVirus(Observer *owner, Board *board) : 
	Ability{"Highly Transmissible Virus", "Input: <Link> | Desc: Choose to infect one of your viruses as highly transmissible. When infected, any players that download the selected virus will also become a virus. If no data exists, change one your opponent's viruses to a data. If no viruses exist, then the ability is directly marked as used", owner, board} {}

void HTVirus::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Highly Transmissible Virus ability.");
	}
	
	Link *target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player && target_link->isVirus()) {
		board->infectLink(link_char, player);
		markUsed();
	} else {
		throw std::invalid_argument("Invalid use of Highly Transmissible Virus ability.");
	}
}
