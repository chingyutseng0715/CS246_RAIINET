export module LinkBoost;

import <string>;
import Ability;

export class LinkBoost: public Ability {
	public:
		LinkBoost(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
