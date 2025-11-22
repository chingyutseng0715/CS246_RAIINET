export module GameMode;

import <vector>;
import <memory>;
import Board;
import Player;

export enum class GameState {
	Menu,
	GameRunning,
	GameOver
};

export class GameMode {
	protected:
		std::shared_ptr<Board> board;
		std::vector<std::shared_ptr<Player>> players;
		GameState game_state = GameRunning; // for now, change to Menu later once it's set up
	public:
		GameMode(Board board, std::vector<Player> players);
		void operatingGame();
		void displayMenu();
		void displayGameOver();
		virtual void runGame() = 0;
		void setGameState(GameState new_game_state); // may not need since game_state is protected
		virtual ~GameMode();
};
