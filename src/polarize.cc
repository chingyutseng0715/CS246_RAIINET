export module Polarize;

import <string>;
import Ability;

export class Polarize: public Ability {
	public:
		Polarize(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
