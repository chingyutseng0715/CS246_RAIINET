export module Theft;

import <string>;
import Observer;
import Board;
import Ability;

export class Theft: public Ability {
	public:
		// Ctor: Creates a Theft ability
		// Param:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		Theft(Observer *owner, Board *board);

		// Executes the Theft ability operation
		// Param:
		//   command - A string containing the player index to steal from
		// Req: 
		//   - The target player must exist and be different from the ability owner
		//   - The target player must have at least one unused ability
		// Throws: std::invalid_argument if command format is invalid or target is invalid
		void operatingAbility(std::string command) override;
};
