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
const std::string ASCII_WINNER_MESSAGE_END = R"(
                  ░██                      
                                           
░██    ░██    ░██ ░██░████████   ░███████  
░██    ░██    ░██ ░██░██    ░██ ░██        
 ░██  ░████  ░██  ░██░██    ░██  ░███████  
  ░██░██ ░██░██   ░██░██    ░██        ░██ 
   ░███   ░███    ░██░██    ░██  ░███████  
                                           
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
	GameState game_state;
	std::unique_ptr<Board> board;

	const int num_players;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<PlayerID> player_order;
	int remaining_players;
	std::vector<bool> eliminated_players;

	bool using_file = false;
	std::ifstream sequence_file{}; // Initialize the ifstream with {}

	public:
		GameMode(const ProcessedInput &input);
		void operatingGame();
		void displayMenu();
		PlayerID runGame();
		void displayGameOver(PlayerID winner);
		bool conductPlayerTurn(std::shared_ptr<Player> current_player_ptr);
};
