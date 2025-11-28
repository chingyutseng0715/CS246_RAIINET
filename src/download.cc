export module Download;

import <string>;
import Observer;
import Board;
import Ability;

export class Download: public Ability {
	public:
		// Ctor: Creates a Download ability
		// Param:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		Download(Observer *owner, Board *board);

		// Executes the Download ability operation
		// Param:
		//   command - A string containing the link character to download
		// Req: 
		//   - The target link must exist on the board
		//   - The target link must belong to an opponent (not the ability owner)
		// Throws: std::invalid_argument if command format is invalid or target is invalid
		void operatingAbility(std::string command) override;
};
