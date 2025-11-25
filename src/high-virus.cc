export module highVirus;

import <string>;
import Ability;

export class highVirus: public Ability {
	public:
		highVirus(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
