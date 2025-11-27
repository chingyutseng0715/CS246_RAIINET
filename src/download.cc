export module Download;

import <string>;
import Observer;
import Board;
import Ability;

export class Download: public Ability {
	public:
		Download(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
