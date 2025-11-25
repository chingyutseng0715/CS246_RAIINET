module HTVirus;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

HTVirus::HTVirus(Observer *owner, Board *board)
    : Ability{"Highly Transmissible Virus", "Attach to virus, when infected make downloader's downloaded data become virus, if no data change one of it's virus on board to data, if no virus then the ability is directly mark used", owner, board} {}

void HTVirus::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Highly Transmissible Virus ability");
	}
	
	Link *target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player && target_link->isVirus()) {
		board->infectLink(link_char, player);
		markUsed();
	}
}
