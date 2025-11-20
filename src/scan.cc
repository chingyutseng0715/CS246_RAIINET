export module Scan;

import <string>;
import Ability;

export class Scan: public Ability {
	public:
		void operatingAbility(std::string command) override;
};
