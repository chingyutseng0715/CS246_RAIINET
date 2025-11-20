export module Download;

import <string>;
import Ability;

export class Download: public Ability {
	public:
		void operatingAbility(std::string command) override;
};
