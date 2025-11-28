module Theft;

import <iostream>;
import <string>;
import <sstream>;
import <stdexcept>;
import Constants;
import Ability;
import Board;
import Observer;
import Link;

Theft::Theft(Observer *owner, Board *board) : 
	Ability{"Theft", "Input: <Player #> | Desc: Steal the first, unused ability in a player's index", owner, board} {}

void Theft::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int player_number;

	if (!(iss >> player_number)) {
		throw std::invalid_argument("Invalid command for Theft ability.");
	}
	
	std::string player_name = PLAYER_NAME_PREFIX + std::to_string(player_number);
	Observer *opponent = board->getPlayer(player_name);
	
	if (!opponent) {
		throw std::invalid_argument("Invalid player name.");
	}
	
	if (opponent == player) {
		throw std::invalid_argument("You cannot steal from yourself.");
	}
	
	char stolen_ability_char = opponent->removeAbility();
	if (stolen_ability_char != NULL_ABILITY) {
		player->addAbility(stolen_ability_char);
	}
	markUsed();
}
