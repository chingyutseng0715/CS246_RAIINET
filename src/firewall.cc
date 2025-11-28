export module Firewall;

import <string>;
import Observer;
import Board;
import Ability;

export class Firewall: public Ability {
	public:
		// Ctor: Creates a Firewall ability
		// Parameters:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		Firewall(Observer *owner, Board *board);

		// Executes the Firewall ability operation
		// Param:
		//   command - A string containing the row and column coordinates
		// Req: 
		//   - The target square must be empty
		//   - The coordinates must be within valid board boundaries
		// Throws: std::invalid_argument if command format is invalid
		void operatingAbility(std::string command) override;
};
