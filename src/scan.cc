export module Scan;

import <string>;
import Observer;
import Board;
import Ability;

export class Scan: public Ability {
	public:
		Scan(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
