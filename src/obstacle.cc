export module Obstacle;

import <string>;
import Observer;
import Board;
import Ability;

export class Obstacle: public Ability {
	public:
		// Ctor: Creates an Obstacle ability
		// Param:
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board
		Obstacle(Observer *owner, Board *board);

		// Executes the Obstacle ability operation
		// Param:
		//   command - A string containing row, column, and direction
		//             Direction: 'v' (vertical), 'h' (horizontal)
		// Req: 
		//   - All three obstacle squares must be empty
		//   - All coordinates must be within valid board boundaries
		// Throws: std::invalid_argument if command format is invalid or squares are not empty
		void operatingAbility(std::string command) override;
};
