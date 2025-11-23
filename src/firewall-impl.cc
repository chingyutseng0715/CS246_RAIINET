module Firewall;
import Link;
import Ability;
import Board;
import <string>;
import <sstream>;
import <stdexcept>;

Firewall::Firewall(Observer *owner, Board *board)
    : Ability{"Firewall", "Place on empty square, reveals and opponent downloads viruses passing through", owner, board} {}

void Firewall::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int row, col;
	
	if (!(iss >> row >> col)) {
		throw std::invalid_argument("Invalid command for Firewall ability");
	}
	
	board->setFireWall(row, col, player);
}