module highVirus;
import Board;
import Ability;
import Link;
import <sstream>;
import <string>;
import <stdexcept>;

highVirus::highVirus(Observer *owner, Board *board)
    : Ability{"High Transmissible Virus", "Attach to virus, when infected make downloader's downloaded data become virus, if no data change one of it's virus on board to data, it no virus then the ability is directly mark used", owner, board} {}

void highVirus::operatingAbility(std::string command) {
	std::istringstream iss(command);
	char link_char;
	
	if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for high transmissible virus ability");
	}
	
	Link *target_link = board->getLink(link_char);
	if (target_link && target_link->getPlayer() == player && target_link->getType() == "Virus") {
		board->infectLink(link_char, player);
		markUsed();
	}
}