export module Download;

import <string>;
import Ability;

export class Download: public Ability {
	public:
		Download(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
