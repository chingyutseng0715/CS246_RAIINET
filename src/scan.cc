export module Scan;

import <string>;
import Observer;
import Board;
import Ability;

export class Scan: public Ability {
	public:
		// Ctor: Creates a Scan ability
		// Parameters:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		Scan(Observer *owner, Board *board);

		// Executes the Scan ability operation
		// Param:
		//   command - A string containing the link character to scan 
		// Req: 
		//   - The target link must exist on the board
		// Throws: std::invalid_argument if command format is invalid
		void operatingAbility(std::string command) override;
};
