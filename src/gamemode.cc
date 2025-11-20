export module GameMode;

import <vector>;
import Board;
import Player;

export class GameMode {
	protected:
		Board board;
		std::vector<Observer *> players;
	public:
		virtual void operatingGame() = 0;
		virtual ~Mode();
};
