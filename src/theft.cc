export module Theft;

import <string>;
import Ability;

export class Theft: public Ability {
	public:
	 Theft(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};