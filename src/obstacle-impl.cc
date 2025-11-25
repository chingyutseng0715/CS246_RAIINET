module Obstacle;

import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Obstacle::Obstacle(Observer *owner, Board *board)
    : Ability{"Obstacle", "Place on empty 3*1 square, acts like a wall", owner, board} {}

void Obstacle::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int row, col;
    char dir;
	
	if (!(iss >> row >> col >> dir)) {
		throw std::invalid_argument("Invalid command for Obstacle ability");
	}
	
	board->setObstacle(row, col, dir);
    markUsed();
}
