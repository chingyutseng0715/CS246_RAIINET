module HTVirus;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

HTVirus::HTVirus(Observer *owner, Board *board) : 
	Ability{"Highly Transmissible Virus", "Input: <Owned Virus> | Desc: Choose to infect one of your viruses as highly transmissible. When the player downloads the infected virus, all of the previous data downloaded by the player will turn into viruses. If no data is found, one of the opponent's data on the board will become a virus. If neither works, no effect occurs", owner, board} {}

void HTVirus::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Highly Transmissible Virus ability.");
	}
	
	Link *target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player && target_link->isVirus() && !target_link->isDownloaded()) {
		board->infectLink(link_char, player);
		markUsed();
	} else {
		throw std::invalid_argument("Invalid use of Highly Transmissible Virus ability.");
	}
}
