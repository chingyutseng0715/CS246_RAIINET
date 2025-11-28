export module GameMode;

import <iostream>;
import <fstream>;
import <sstream>;
import <string>;
import <vector>;
import <memory>;
import <stdexcept>;
import Constants;
import CommandLineProcessor;
import TwoPlayerBoard;
import FourPlayerBoard;
import Board;
import Player;
import Link;
import xwindow;

// Constant (raw) strings, serving as ASCII art for the Menu and GameOver screens
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
const std::string ASCII_INSTRUCTIONS = R"(
▄▖          ▌▄▖  ▗     ▌  ▗     ▄▖▜     
▙▌▛▘█▌▛▘▛▘   ▙▖▛▌▜▘█▌▛▘   ▜▘▛▌  ▙▌▐ ▀▌▌▌
▌ ▌ ▙▖▄▌▄▌   ▙▖▌▌▐▖▙▖▌    ▐▖▙▌  ▌ ▐▖█▌▙▌
                                      ▄▌
)";
const std::string ASCII_PLAYER_ONE = R"(

░█████████  ░██                                                ░██   
░██     ░██ ░██                                              ░████   
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████      ░██   
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███          ░██   
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██           ░██   
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██           ░██   
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██         ░██████ 
                                  ░██                                
                            ░███████                                 )";
const std::string ASCII_PLAYER_TWO = R"(

░█████████  ░██                                               ░██████  
░██     ░██ ░██                                              ░██   ░██ 
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████          ░██ 
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███          ░█████  
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██          ░██      
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██         ░██       
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██         ░████████ 
                                  ░██                                  
                            ░███████                                   )";
const std::string ASCII_PLAYER_THREE = R"(

░█████████  ░██                                               ░██████  
░██     ░██ ░██                                              ░██   ░██ 
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████          ░██ 
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███          ░█████  
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██               ░██ 
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██         ░██   ░██ 
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██          ░██████  
                                  ░██                                  
                            ░███████                                   )";
const std::string ASCII_PLAYER_FOUR = R"(

░█████████  ░██                                                 ░████   
░██     ░██ ░██                                                ░██ ██   
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████     ░██  ██   
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███        ░██   ██   
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██         ░█████████ 
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██              ░██   
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██              ░██   
                                  ░██                                   
                            ░███████                                    )";
const std::string ASCII_NOBODY = R"(

░███    ░██            ░██                          ░██            
░████   ░██            ░██                          ░██            
░██░██  ░██  ░███████  ░████████   ░███████   ░████████ ░██    ░██ 
░██ ░██ ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ 
░██  ░██░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ 
░██   ░████ ░██    ░██ ░███   ░██ ░██    ░██ ░██   ░███ ░██   ░███ 
░██    ░███  ░███████  ░██░█████   ░███████   ░█████░██  ░█████░██ 
                                                               ░██ 
                                                         ░███████  )";
const std::string ASCII_WINNER_MESSAGE_POSTFIX = R"(
                  ░██                      
                                           
░██    ░██    ░██ ░██░████████   ░███████  
░██    ░██    ░██ ░██░██    ░██ ░██        
 ░██  ░████  ░██  ░██░██    ░██  ░███████  
  ░██░██ ░██░██   ░██░██    ░██        ░██ 
   ░███   ░███    ░██░██    ░██  ░███████  
                                           
)";

export enum class GameState {
	Menu,
	GameRunning,
	GameOver
};

export enum class PlayerID {
	Player1,
	Player2,
	Player3,
	Player4,
	Nobody
};

export class GameMode {
	GameState game_state = GameState::Menu;
	std::unique_ptr<Board> board;

	const int num_players;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<PlayerID> player_order;
	int remaining_players;
	std::vector<bool> eliminated_players;

	std::vector<std::ifstream> sequence_file;

	bool graphics_enabled;
	std::vector<std::shared_ptr<Xwindow>> windows;
	
	void refreshWindow(std::shared_ptr<Xwindow> window, std::shared_ptr<Player> player);
	public:
		// Constructor; takes input that's been pre-processed from the command line
		GameMode(const ProcessedInput &input);
		// Operate the different gameState
		void operatingGame();

		// displayMenu() Displays a basic Menu screen, starting the game once the player hits 'Enter'
		void displayMenu();

		// runGame() Runs the game of RAIInet and returns the winner's PlayerID when the game finishes
		PlayerID runGame();

		// displayGameOver(winner) Displays a basic GameOver screen that highlights the winner
		void displayGameOver(PlayerID winner);

		// conductPlayerTurn(current_player_ptr) Conducts a single turn for the player being pointed
		//   to by current_player_ptr
		bool conductPlayerTurn(std::shared_ptr<Player> current_player_ptr);
};
