export module Board;

import <iostream>;
import <vector>;
import <map>;
import <memory>;
import <string>;
import Observer;
import Link;

export class Board {
	protected:
		int height;
		int width;
		std::vector<Observer *> players;
		std::vector<std::vector<char>> theBoard;
		std::map<char, std::shared_ptr<Link>> charLinkMapping;
		std::map<std::pair<int, int>, Observer *> charOwner;
	public:
		Board(int height, int width);
		virtual void addPlayer(Observer *player, std::string linkorder) = 0;
		void updateLink(char link_char, std::string direction);
		void setFireWall(int row, int col, Observer *player);
		void infectLink(char link_char, Observer *player);
		void setObstacle(int row, int col, char direction);
		Link * getLink(char link_char);
		char getState(int row, int col);
		Observer * getcharOwnership(int row, int col);
		Observer * getPlayer(std::string name);
		void printBoard(std::ostream &os, Observer *player);
};

