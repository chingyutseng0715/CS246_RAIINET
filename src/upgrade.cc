export module Upgrade;

import <string>;
import Ability;

export class Upgrade: public Ability {
	public:
		Upgrade(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};