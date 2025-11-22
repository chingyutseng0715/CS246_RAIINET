export module GameMode;

import <vector>;
import Board;
import Player;

export enum class GameState {
	Menu,
	GameRunning,
	GameOver
};

export class GameMode {
	protected:
		Board board;
		std::vector<Player> players;
		GameState game_state;
	public:
		GameMode(Board board, std::vector<Player> players);
		void operatingGame();
		virtual void runGame() = 0;
		void setGameState(GameState new_game_state); // may not need since game_state is protected
		virtual ~GameMode();
};
