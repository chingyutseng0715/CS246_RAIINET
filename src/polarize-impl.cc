module Polarize;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Polarize::Polarize(Observer *owner, Board *board) : 
    Ability{"Polarize", "Input: <Link> | Desc: Change a data to a virus of the same strength, or vice versa", owner, board} {}

void Polarize::operatingAbility(std::string command){
    std::istringstream iss(command);
    char link_char;
    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Polarize ability.");
	}

    Link *target_link = board->getLink(link_char);
    if (target_link) {
        if (target_link->isVirus()){
            target_link->setType(LinkType::Data);
            markUsed();
        } else {
            target_link->setType(LinkType::Virus);
            markUsed();
        }
    } else {
        throw std::invalid_argument("Invalid use of Polarize ability.");
    }
}
