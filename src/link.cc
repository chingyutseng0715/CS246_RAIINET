export module Link;

import <iostream>;
import Observer;

export class Link {
	Observer *player;
	char symbol;
	char type;
	int strength;
	int move_per_step;
	bool revealed;
	bool downloaded;
	
	public:
		Link(Observer *player, char symbol, char type, int strength, int move_per_step = 1);
		auto operator<=>(const Link &other);
		void setStrength(int strength);
		void setType(char type);
		void setMovePerStep(int move_per_step);
		void Reveal();
		void Download();
		Observer* getPlayer();
		int getStrength();
		int getMovePerStep();
		bool isVirus();
		bool isRevealed();
		bool isDownloaded();
	friend std::ostream &operator<<(std::ostream &, const Link &);
};

export std::ostream &operator<<(std::ostream &os, const Link &link);
