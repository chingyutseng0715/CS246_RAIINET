module Theft;

import <string>;
import <sstream>;
import <stdexcept>;
import <random>;
import Ability;
import Board;
import Link;

Theft::Theft(Observer *owner, Board *board)
	: Ability{"Theft", "Steal an assigned other player's ability", owner, board} {}

void Theft::operatingAbility(std::string command) {
	std::istringstream iss(command);
	int player_index;


    if (!(iss >> player_index)) {
		throw std::invalid_argument("Invalid command for Theft ability");
	}
	
	Observer *opponent = board->getPlayer(player_index);
	
	if (opponent && opponent != player) {
		int ability_count = opponent->getAbilityAmount();
		
		if (ability_count > 0) {

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, ability_count - 1);
			int random_index = dis(gen);
			
			Ability &stolen_ability = opponent->getAbilityAt(random_index);
			player->addAbility(stolen_ability);
			opponent->removeAbility(random_index);
			markUsed();
		}
	}
}
