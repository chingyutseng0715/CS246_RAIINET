module Obstacle;
import Link;
import Ability;
import Board;
import <string>;
import <sstream>;
import <stdexcept>;

Obstacle:Obstacle(Observer *owner, Board *board)
    : Ability{"Obstacle", "Place on empty 3*1 square, acts like a wall", owner, board} {}

voidObstacle::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int row, col;
    char dir;
	
	if (!(iss >> row >> col >> dir)) {
		throw std::invalid_argument("Invalid command forObstacle ability");
	}
	
	board->setObstacle(row, col, dir);
}
