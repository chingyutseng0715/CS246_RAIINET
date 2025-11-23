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

    Link *target_link = board->getlink(link_char);
    if (target_link && target_link->getPlayer() == player) {
        std::string curType = target_link->getType();
        if (curType == "Virus"){
            target_link->setType("Data");
        } else if(curType == "Data") {
            target_link->setType("Virus");
        }
    }
}