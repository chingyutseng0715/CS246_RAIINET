module Obstacle;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Obstacle::Obstacle(Observer *owner, Board *board) : 
	Ability{"Obstacle", "Input: <Row> <Col> <Dir> | Desc: Place a 3x1 wall, with the selected square as the center. All squares that the wall will occupy must be non-empty", owner, board} {}

void Obstacle::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int row, col;
    char dir;
	
	if (!(iss >> row >> col >> dir)) {
		throw std::invalid_argument("Invalid command for Obstacle ability.");
	}
	
	board->setObstacle(row, col - 1, dir);
    markUsed();
}
