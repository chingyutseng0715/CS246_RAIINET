module Firewall;
import Link;
import Ability;
import Board;
import <string>;
import <sstream>;

Firewall::Firewall(Observer *owner, Board *board)
    : Ability{"Firewall", "Place on empty square, reveals and opponent downloads viruses passing through", owner, board} {}

void Firewall::operatingAbility(std::string command) {
    std::istringstream iss(command)
    int row, col;
    iss >> row >> col;

    if (board->getState(row, col) == '.'){
        board->updateBoard(row, col, 'm');
    }
}