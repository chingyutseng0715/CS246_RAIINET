module Download;

import <string>;
import <sstream>;
import <stdexcept>;
import Observer;
import Ability;
import Board;
import Link;

Download::Download(Observer *owner, Board *board)
    :Ability("Download", "Input: <Link> | Desc: Immediately download an opponent's link", owner, board){}

void Download::operatingAbility(std::string command){
    std::istringstream iss(command);
    char link_char;

    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Download ability.");
	}
	
	Link *link = board->getLink(link_char);
    if (link->getPlayer() != player) {
		board->downloadLink(player, link_char);
        markUsed();
    } else {
        throw std::invalid_argument("Invalid use of Download ability.");
    }
}
