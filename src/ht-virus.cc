export module HTVirus;

import <string>;
import Observer;
import Board;
import Ability;

export class HTVirus: public Ability {
	public:
		HTVirus(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
