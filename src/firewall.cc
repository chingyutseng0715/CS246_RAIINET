export module Firewall;

import <string>;
import Ability;

export class Firewall: public Ability {
	public:
		void operatingAbility(std::string command) override;
};
