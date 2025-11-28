export module LinkBoost;

import <string>;
import Observer;
import Board;
import Ability;

export class LinkBoost: public Ability {
	public:
		// Ctor: Creates a LinkBoost ability
		// Param:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		LinkBoost(Observer *owner, Board *board);

		// Executes the LinkBoost ability operation
		// Param:
		//   command - A string containing the link character to boost
		// Req: 
		//   - The target link must exist on the board
		//   - The target link must belong to the ability owner
		// Throws: std::invalid_argument if command format is invalid or target is invalid
		void operatingAbility(std::string command) override;
};
