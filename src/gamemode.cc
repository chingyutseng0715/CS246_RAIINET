export module GameMode;

import <iostream>;
import <string>;
import <vector>;
import <memory>;
import Board;
import Player;

const std::string ASCII_TITLE = R"(
 ███████████     █████████   █████ █████                      █████   
░░███░░░░░███   ███░░░░░███ ░░███ ░░███                      ░░███    
 ░███    ░███  ░███    ░███  ░███  ░███  ████████    ██████  ███████  
 ░██████████   ░███████████  ░███  ░███ ░░███░░███  ███░░███░░░███░   
 ░███░░░░░███  ░███░░░░░███  ░███  ░███  ░███ ░███ ░███████   ░███    
 ░███    ░███  ░███    ░███  ░███  ░███  ░███ ░███ ░███░░░    ░███ ███
 █████   █████ █████   █████ █████ █████ ████ █████░░██████   ░░█████ 
░░░░░   ░░░░░ ░░░░░   ░░░░░ ░░░░░ ░░░░░ ░░░░ ░░░░░  ░░░░░░     ░░░░░  
                                                                      
)";

const std::string PLAYER1_VALID_LINKS = "abcdefgh";
const std::string PLAYER2_VALID_LINKS = "ABCDEFGH";
// const std::string PLAYER3_VALID_LINKS = 
// const std::string PLAYER4_VALID_LINKS = 
const int DATA_DOWNLOADS_TO_WIN = 4;
const int VIRUS_DOWNLOADS_TO_LOSE = 4;

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
		std::ifstream sequence_file;
	public:
		GameMode(std::shared_ptr<Board> board);
		void operatingGame();
		void displayMenu();
		virtual Winner runGame() = 0;
		void displayGameOver();
		// virtual ~GameMode();
};
