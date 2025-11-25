module Polarize;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Polarize::Polarize(Observer *owner, Board *board)
: Ability{"Polarize", "Changes the link's type to it's opposite with the same stength", owner, board} {}

void Polarize::operatingAbility(std::string command){
    std::istringstream iss(command);
    char link_char;
    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Polarize ability");
	}

    Link *target_link = board->getLink(link_char);
    if (target_link && target_link->getPlayer() == player) {
        if (target_link->isVirus()){
            target_link->setType('D');
            markUsed();
        } else {
            target_link->setType('V');
            markUsed();
        }
    }
}
