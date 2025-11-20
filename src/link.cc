export module Link;

import <iostream>;
import <string>;
import Observer;
import Board;

export class Link {
	Observer *player;
	Board *board;
	char link_char;
	std::string type;
	int strength;
	int row;
	int col;
	int move_per_step;
	bool revealed;
	bool downloaded;
	
	public:
		Link(Observer *player, Board *board, char link_char, std::string name, int move_per_step);
		auto operator<=>(const Link &other);
		void setStrength(int strength);
		void setType(std::string type);
		void setRevealed(bool revealed);
		void setDownloaded(bool downloaded);
		std::string getType();
		bool isRevealed();
		bool isDownloaded();
		void movingLink(char direction);
	friend std::ostream &operator<<(std::ostream &, const Link &);
};

export std::ostream &operator<<(std::ostream &os, const Link &link);
