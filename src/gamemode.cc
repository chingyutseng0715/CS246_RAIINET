export module GameMode;

import <iostream>;
import <fstream>;
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
const std::string ASCII_INSTRUCTIONS = R"(
▄▖          ▌▄▖  ▗     ▌  ▗     ▄▖▜     
▙▌▛▘█▌▛▘▛▘   ▙▖▛▌▜▘█▌▛▘   ▜▘▛▌  ▙▌▐ ▀▌▌▌
▌ ▌ ▙▖▄▌▄▌   ▙▖▌▌▐▖▙▖▌    ▐▖▙▌  ▌ ▐▖█▌▙▌
                                      ▄▌
)";
/*const std::string ASCII_INSTRUCTIONS = R"(
▗▄▄▖ ▗▄▄▖ ▗▄▄▄▖ ▗▄▄▖ ▗▄▄▖    ▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▄▖▗▄▄▖     ▗▄▄▄▖▗▄▖     ▗▄▄▖ ▗▖    ▗▄▖▗▖  ▗▖
▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌   ▐▌       ▐▌   ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌      █ ▐▌ ▐▌    ▐▌ ▐▌▐▌   ▐▌ ▐▌▝▚▞▘ 
▐▛▀▘ ▐▛▀▚▖▐▛▀▀▘ ▝▀▚▖ ▝▀▚▖    ▐▛▀▀▘▐▌ ▝▜▌  █  ▐▛▀▀▘▐▛▀▚▖      █ ▐▌ ▐▌    ▐▛▀▘ ▐▌   ▐▛▀▜▌ ▐▌  
▐▌   ▐▌ ▐▌▐▙▄▄▖▗▄▄▞▘▗▄▄▞▘    ▐▙▄▄▖▐▌  ▐▌  █  ▐▙▄▄▖▐▌ ▐▌      █ ▝▚▄▞▘    ▐▌   ▐▙▄▄▖▐▌ ▐▌ ▐▌  
                                                                                            
)";
*/
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
                            ░███████                                 
                                                                     
)";
const std::string ASCII_PLAYER_TWO = R"(
░█████████  ░██                                               ░██████  
░██     ░██ ░██                                              ░██   ░██ 
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████          ░██ 
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███          ░█████  
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██          ░██      
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██         ░██       
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██         ░████████ 
                                  ░██                                  
                            ░███████                                   
                                                                       
)";
const std::string ASCII_PLAYER_THREE = R"(
░█████████  ░██                                               ░██████  
░██     ░██ ░██                                              ░██   ░██ 
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████          ░██ 
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███          ░█████  
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██               ░██ 
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██         ░██   ░██ 
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██          ░██████  
                                  ░██                                  
                            ░███████                                   
                                                                       
)";
const std::string ASCII_PLAYER_FOUR = R"(
░█████████  ░██                                                 ░████   
░██     ░██ ░██                                                ░██ ██   
░██     ░██ ░██  ░██████   ░██    ░██  ░███████  ░██░████     ░██  ██   
░█████████  ░██       ░██  ░██    ░██ ░██    ░██ ░███        ░██   ██   
░██         ░██  ░███████  ░██    ░██ ░█████████ ░██         ░█████████ 
░██         ░██ ░██   ░██  ░██   ░███ ░██        ░██              ░██   
░██         ░██  ░█████░██  ░█████░██  ░███████  ░██              ░██   
                                  ░██                                   
                            ░███████                                    
                                                                        
)";
const std::string ASCII_NOBODY = R"(
░███    ░██            ░██                          ░██            
░████   ░██            ░██                          ░██            
░██░██  ░██  ░███████  ░████████   ░███████   ░████████ ░██    ░██ 
░██ ░██ ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ 
░██  ░██░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ ░██    ░██ 
░██   ░████ ░██    ░██ ░███   ░██ ░██    ░██ ░██   ░███ ░██   ░███ 
░██    ░███  ░███████  ░██░█████   ░███████   ░█████░██  ░█████░██ 
                                                               ░██ 
                                                         ░███████  
                                                                   
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

export enum class PlayerID {
	Player1,
	Player2,
	Player3,
	Player4,
	Nobody
};

export class GameMode {
	protected:
		std::shared_ptr<Board> board;
		GameState game_state = GameState::GameRunning; // fine for now, CHANGE to GameState::Menu later once it's set up
		std::vector<std::shared_ptr<Player>> players;
		std::vector<std::string> ability_orders; // 'may' not be needed
		std::vector<std::string> link_orders; // 'may' not be needed
		//std::ifstream sequence_file;
		bool using_file = false;
	public:
		GameMode(std::shared_ptr<Board> board);
		void operatingGame();
		void displayMenu();
		virtual PlayerID runGame() = 0;
		void displayGameOver(PlayerID winner);
		virtual ~GameMode();
};
