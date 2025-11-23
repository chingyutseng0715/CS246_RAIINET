module Download;
import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
Import Link;

Download::Download(Observer *owner, Board *board)
    :Ability("Download", "Immediately download opponent's link(no reveal)", owner, board){}

void Download::operatingAbility(std::string command){
    std::istringstream iss(command);
    char link_char;

    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Download ability");
	}

    Link *target_link = board->getLink(link_char);
    if (target_link && target_link->getPlayer() != player){
        player->download(link_char);
        markUsed();
    }
}