module LinkBoost;
import Board;
import Ability;
import Link;
import <sstream>;
import <string>;
LinkBoost::LinkBoost(Observer *owner, Board *board)
    : Ability{"Link Boost", "Move 2 steps and also have the ability to jump over obstacles", owner, board} {}

void LinkBoost::operatingAbility(std::string command){
    //Deal with cerr after
    std::istringstream iss(command);
    char link_char;
    iss >> link_char;

    Link *target_link = board->getlink(link_char);
    if (target_link && target_link->getPlayer() == player) {
        target_link->setMovePerStep(2);
    }
}