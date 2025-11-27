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
		Link(Observer *player, char symbol, char type, int strength, int move_per_step = DEFAULT_STEPS_PER_MOVE);
		std::strong_ordering operator<=>(const Link &other) const;
		void setStrength(int strength);
		void setType(LinkType type);
		void setMovePerStep(int move_per_step);
		void Reveal();
		void Download();
		void Infect();
		Observer * getPlayer();
		char getSymbol();
		int getStrength();
		int getMovePerStep();
		bool isVirus();
		bool isInfected();
		bool isRevealed();
		bool isDownloaded();
		void printLink(std::ostream &os, bool secret = true);
};
