module Firewall;

import <string>;
import <sstream>;
import <stdexcept>;
import Link;
import Ability;
import Board;

Firewall::Firewall(Observer *owner, Board *board)
    : Ability{"Firewall", "Input: <Row> <Col> | Desc: Place a firewall on an empty square. The firewall reveals all links that pass through it, and if any are viruses, it forces opponents to download them", owner, board} {}

void Firewall::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int row, col;
	
	if (!(iss >> row >> col)) {
		throw std::invalid_argument("Invalid command for Firewall ability.");
	}
	
	board->setFireWall(row, col - 1, player);
    markUsed();
}
