export module HTVirus;

import <string>;
import Observer;
import Board;
import Ability;

export class HTVirus: public Ability {
	public:
		// Ctor: Creates a High Transmissible Virus ability
		// Param:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		HTVirus(Observer *owner, Board *board);

		// Executes the High Transmissible Virus ability operation
		// Param:
		//   command - A string containing the link character to infect
		// Req: 
		//   - The target link must exist on the board
		//   - The target link must be a virus (not data)
		//   - The target link must not already be infected
		// Throws: std::invalid_argument if command format is invalid or target is invalid
		void operatingAbility(std::string command) override;
};
