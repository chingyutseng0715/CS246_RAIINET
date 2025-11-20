export module Link;

import <iostream>;
import <string>;
import Observer;

export class Link {
	Observer *player;
	std::string type;
	int strength;
	int move_per_step;
	bool revealed;
	bool downloaded;
	
	public:
		Link(Observer *player, std::string name, int move_per_step);
		auto operator<=>(const Link &other);
		void setStrength(int strength);
		void setType(std::string type);
		void setRevealed(bool revealed);
		void setDownloaded(bool downloaded);
		void setMoveperstep(int move_per_step);
		Observer* getPlayer();
		std::string getType();
		bool isRevealed();
		bool isDownloaded();
	friend std::ostream &operator<<(std::ostream &, const Link &);
};

export std::ostream &operator<<(std::ostream &os, const Link &link);
