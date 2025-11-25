export module Firewall;

import <string>;
import Observer;
import Board;
import Ability;

export class Firewall: public Ability {
	public:
		Firewall(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
