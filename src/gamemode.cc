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

export enum class Player {
	Player1,
	Player2,
	Player3,
	Player4
};

export class GameMode {
	protected:
		std::shared_ptr<Board> board;
		std::vector<std::string> ability_orders; // 'may' not be needed
		std::vector<std::string> link_orders; // 'may' not be needed
		std::vector<std::shared_ptr<Player>> players;
		GameState game_state = GameRunning; // fine for now, change to Menu later once it's set up
	public:
		GameMode(std::shared_ptr<Board> board);
		void operatingGame();
		void displayMenu();
		virtual Winner runGame() = 0;
		void displayGameOver();
		// virtual ~GameMode();
};
