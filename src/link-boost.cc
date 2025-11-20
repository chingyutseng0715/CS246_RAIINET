export module LinkBoost;

import <string>;
import Ability;

export class LinkBoost: public Ability {
	public:
		void operatingAbility(std::string command) override;
};
