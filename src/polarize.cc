export module Polarize;

import <string>;
import Ability;

export class Polarize: public Ability {
	public:
		void operatingAbility(std::string command) override;
};
