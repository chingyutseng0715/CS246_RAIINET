module Upgrade;
import Board;
import Ability;
import Link;
import <sstream>;
import <string>;
import <stdexcept>;
Upgrade::Upgrade(Observer *owner, Board *board)
    : Ability{"Upgrade", "Upgrade the strength of virus or data", owner, board} {}

void Upgrade::operatingAbility(std::string command){

    std::istringstream iss(command);
    char link_char;
    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Upgrade ability");
	}

    Link *target_link = board->getLink(link_char);
    if (target_link && target_link->getPlayer() == player) {
        int cur_strength = target_link->getStrength();
        target_link->setStrength(cur_strength + 1);
        markUsed();
    }
}