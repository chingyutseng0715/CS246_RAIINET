export module Link;

import <iostream>;
import <compare>;
import Constants;
import Observer;

export enum class LinkType {
	Data = DATA_CHAR,
	Virus = VIRUS_CHAR
};

export class Link {
	Observer *player;
	char symbol;
	LinkType type;
	int strength;
	int move_per_step;
	bool revealed;
	bool downloaded;
	bool infected;
	
	public:
		// Basic constructor
		Link(Observer *player, char symbol, char type, int strength, 
			 int move_per_step = DEFAULT_STEPS_PER_MOVE);

		// Return a strong_ordering given the strength of this and the other link
		std::strong_ordering operator<=>(const Link &other) const;

		// setStrength(strength) set the link to have the given strength
		void setStrength(int strength);

		// setType(type) set the link to have the given type
		void setType(LinkType type);

		// Boost() increase the link's move_per_step by 1 (to be used by the Boost ability)
		void Boost();

		// Reveal() set the link's revealed status to true (to be used by the HTVirus ability)
		void Reveal();

		// Download() set the link's downloaded status to true (to be used by the Download ability)
		void Download();

		// Infect() set the link's infected status to true (to be used by the Scan ability)
		void Infect();

		// getPlayer() Return the link's owner/player as an Observer *
		Observer * getPlayer();

		// getSymbol() Return the link's symbol char
		char getSymbol();

		// getStrength() Return the link's strength
		int getStrength();

		// getMovePerStep() Return the link's move_per_step
		int getMovePerStep();

		// isVirus() Return whether the link is a virus
		bool isVirus();

		// isInfected() Return whether the link is infected
		bool isInfected();

		// isRevealed() Return whether the link is reavead
		bool isRevealed();

		// isDownloaded() Return whether the link is downloaded
		bool isDownloaded();

		// isVirus() Print the type and strength of the link to the given os, based on the secret status
		void printLink(std::ostream &os, bool secret = true);
};
