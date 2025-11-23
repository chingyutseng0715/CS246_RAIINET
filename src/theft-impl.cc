module Theft;
import <string>;
import <sstream>;
import <stdexcept>;
import Ability;
import Board;
import Link;

Theft::Theft(Observer *owner, Board *board)
	: Ability{"Theft", "Steal an assigned other player's ability", owner, board} {}

void Thief::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int player_index;
	if (!(iss >> player_index)) {
		throw std::invalid_argument("Invalid command for Theft ability");
	}
	
	Observer *opponent = board->getPlayer(player_index);
	
	if (opponent && opponent != player) {
		Ability *stolen_ability = board->getRandomAbility(opponent);
		
		if (stolen_ability) {
			player->addAbility(*stolen_ability);
		}
	}
}