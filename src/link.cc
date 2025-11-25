export module Link;

import <iostream>;
import <compare>;
import Observer;

export class Link {
	Observer *player;
	char symbol;
	char type;
	int strength;
	int move_per_step;
	bool revealed;
	bool downloaded;
	bool infected;
	
	public:
		Link(Observer *player, char symbol, char type, int strength, int move_per_step = 1);
		std::strong_ordering operator<=>(const Link &other) const;
		void setStrength(int strength);
		void setType(char type);
		void setMovePerStep(int move_per_step);
		void Reveal();
		void Download();
		void Infect();
		Observer* getPlayer();
		int getStrength();
		int getMovePerStep();
		bool isVirus();
		bool isInfected();
		bool isRevealed();
		bool isDownloaded();
		void printLink(std::ostream &os, bool secret = true);
};
