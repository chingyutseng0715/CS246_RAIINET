module Upgrade;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Upgrade::Upgrade(Observer *owner, Board *board) : 
    Ability{"Upgrade", "Input: <Owned Link> | Desc: Upgrade the strength of any of your links by 1", owner, board} {}

void Upgrade::operatingAbility(std::string command) {
    std::istringstream iss(command);
    char link_char;
    if (!(iss >> link_char)) {
		throw std::invalid_argument("Invalid command for Upgrade ability.");
	}

    Link *target_link = board->getLink(link_char);
    if (target_link && target_link->getPlayer() == player) {
        int cur_strength = target_link->getStrength();
        target_link->setStrength(cur_strength + 1);
        markUsed();
    } else {
        throw std::invalid_argument("Invalid use of Upgrade ability.");
    }
}