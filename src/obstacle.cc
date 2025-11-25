export module Obstacle;

import <string>;
import Ability;

export class Obstacle: public Ability {
	public:
		Obstacle(Observer *owner, Board *board);
		void operatingAbility(std::string command) override;
};
