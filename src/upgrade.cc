export module Upgrade;

import <string>;
import Observer;
import Board;
import Ability;

export class Upgrade: public Ability {
	public:
		Upgrade(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};