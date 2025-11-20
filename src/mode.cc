export module Mode;

import <vector>;
import Board;
import Player;

export class Mode {
	protected:
		Board board;
		std::vector<Player> players;
	public:
		virtual void operatingGame() = 0;
		virtual ~Mode();
};
