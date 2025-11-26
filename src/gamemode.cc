export module GameMode;

import <iostream>;
import <fstream>;
import <sstream>;
import <string>;
import <vector>;
import <memory>;
import <stdexcept>;
import Constants;
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
	protected:
		std::unique_ptr<Board> board;
		GameState game_state = GameState::Menu;
		std::vector<std::shared_ptr<Player>> players;
		std::ifstream sequence_file{}; // Initialize the ifstream with {}
		bool using_file = false;
	public:
		GameMode(std::unique_ptr<Board> board);
		void operatingGame();
		void displayMenu();
		virtual PlayerID runGame() = 0;
		void displayGameOver(PlayerID winner);
		bool conductPlayerTurn(std::shared_ptr<Player> current_player_ptr, bool &ability_used);
};
