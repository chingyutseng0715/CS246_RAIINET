export module Ability;

import <iostream>;
import <string>;
import Observer;
import Board;

export class Ability {
	protected:
		std::string name;
		std::string description;
		bool used;
		Observer *player;
		Board *board; 	
	public:
		
		// Ctor: Initializes an ability with its properties
		// Param:
		//   name - name of the ability 
		//   description -  brief description of what the ability does
		//   owner - Pointer to the Observer (player) who owns this ability
		//   board - Pointer to the game board where the ability will be used
		Ability(std::string name, std::string description, Observer *owner, Board *board);

		// Checks if the ability has already been used
		// Return: true if the ability has been used, false otherwise
		bool isUsed();

		// Marks the ability as used, preventing it from being used again
		// Req: None
		void markUsed();

		// Gets the name of the ability
		// Return: The name of the ability as a string
		std::string getName();

		// Pure virtual function that executes the ability's specific operation
		// Param:
		//   command - A string containing the specific arguments needed for the ability
		// Req: Must be implemented by derived classes
		// Throws: std::invalid_argument if command format is invalid or operation fails
		virtual void operatingAbility(std::string command) = 0;


	// Parameters:
	//   os - The output stream to write to
	//   ability - The Ability object to output
	// Returns: Reference to the output stream for chaining
	// Output format: "<name>: <description>"
	friend std::ostream &operator<<(std::ostream &os, const Ability &);
};

export std::ostream &operator<<(std::ostream &os, const Ability &ability);
