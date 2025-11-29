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
		int obstacle_tick;
		std::vector<Observer *> players;
		std::vector<std::vector<char>> theBoard;
		std::map<char, std::shared_ptr<Link>> charLinkMapping;
		
		std::map<std::pair<int, int>, Observer *> charOwner;
		std::map<std::pair<int, int>, Observer *> firewalls;
		
		// battle(link_char, other_link_char) conduct a battle between links with char link_char 
		//   and other_link_char
		void battle(char link_char, char other_link_char);

		// battle(link_char, other_link_char) return the pair of coordinates for the link with 
		//   char symbol
		std::pair<int, int> getIndex(char symbol);
	public:
		// Constructor; create the Board given the height and width
		Board(int height, int width);

		// addPlayer(player, link_order) Pure Virtual function (description in subclasses)
		virtual void addPlayer(Observer *player, std::string link_order) = 0;

		// moveable(link_char) return true if there is a movable position for link_char on the
		//   board. Otherwise, return false
		bool movable(char link_char);

		// downloadLink(player, link_char) Erase the link with symbol link_char from the board and
		//   let the given player download it
		void downloadLink(Observer *player, char link_char);

		// checkFirewall(row, col) check if a firewall exists at the given row and col. If an
		//   opponent's link is on it, reveal it. If it is a virus, make them download it
		void checkFirewall(int row, int col);

		// updateLink(link_char, direction) move the link with symbol link_char in the given direction
		void updateLink(char link_char, std::string direction);

		// setFirewall(row, col, player) set a Firewall that belongs to player at the given row and col
		void setFirewall(int row, int col, Observer *player);

		// infectLink(link_char, player) infect the link with symbol link_char that belongs to player
		void infectLink(char link_char, Observer *player);

		// setObstacle(row, col, direction) set an Obstacle at the given row, col, and direction
		void setObstacle(int row, int col, char direction);

		// getLink(link_char) return a Link * to the link with symbol link_char
		Link * getLink(char link_char);

		// getState(row, col) return the char on/state of the board at the given row and col
		char getState(int row, int col);

		// getObstacleTick() return obstacle_tick (to be used by the Obstacle ability)
		int getObstacleTick();

		// getcharOwnership(row, col)
		Observer * getcharOwnership(int row, int col);

		// getPlayer(name) return an Observer * to the player with the given name. If such a player
		//   doesn't exist, return nullptr
		Observer * getPlayer(std::string name);

		// eliminatePlayer(player) remove the presence of player from the board
		void eliminatePlayer(Observer *player);

		// printBoard(os, player) print the board from the perspective of player to the ostream os
		void printBoard(std::ostream &os, Observer *player);
};

