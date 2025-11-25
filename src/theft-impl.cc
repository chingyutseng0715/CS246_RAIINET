module Theft;

import <string>;
import <sstream>;
import <stdexcept>;
import <random>;
import Ability;
import Board;
import Player;
import Observer;
import Link;

Theft::Theft(Observer *owner, Board *board)
	: Ability{"Theft", "Steal an assigned other player's ability", owner, board} {}

void Theft::operatingAbility(std::string command) {
	std::istringstream iss(command);
	std::string player_name;

	if (!(iss >> player_name)) {
		throw std::invalid_argument("Invalid command for Theft ability");
	}
	
	Observer *opponent = board->getPlayer(player_name);
	
	if (!opponent) {
		throw std::invalid_argument("Invalid player name");
	}
	
	if (opponent == player) {
		throw std::invalid_argument("Cannot steal from yourself");
	}
	
	char stolen_ability_char = opponent->removeAbility();
	player->addAbility(stolen_ability_char);
	markUsed();
}
