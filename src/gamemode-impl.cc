module GameMode;

using std::string, std::cin, std::cout, std::cerr, std::endl, std::to_string, std::ifstream, 
      std::istringstream, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared, 
      std::invalid_argument, std::out_of_range;

GameMode::GameMode(const ProcessedInput &input) : 
    num_players{input.num_players}, remaining_players{input.num_players},
    eliminated_players(input.num_players, false), graphics_enabled{input.graphics_enabled} {
    
    // Create the board and assign the player order based on the number of players
    if (num_players == TWO_PLAYER_NUM) {
        board = make_unique<TwoPlayerBoard>();
        player_order.assign({PlayerID::Player1, PlayerID::Player2});
    } else if (num_players == FOUR_PLAYER_NUM) {
        board = make_unique<FourPlayerBoard>();
        player_order.assign({PlayerID::Player1, PlayerID::Player2, 
                             PlayerID::Player3, PlayerID::Player4});
    }

    // Store each player and pass them to the board
	for (int i = 0; i < num_players; ++i) {
        players.emplace_back(make_shared<Player>(PLAYER_NAME_PREFIX + to_string(i + 1), board.get(), 
                                                 input.ability_orders[i]));
        board->addPlayer(players[i].get(), input.link_orders[i]);
    }
}

void GameMode::operatingGame() {
    while (true) {
        PlayerID winner;
        switch (game_state) {
            case GameState::Menu:
                displayMenu();
                game_state = GameState::GameRunning;
                break;
            case GameState::GameRunning:
                winner = runGame();
                game_state = GameState::GameOver;
                break;
            case GameState::GameOver:
                displayGameOver(winner);
                return;
        }
    }
}

void GameMode::displayMenu() {
    cout << ASCII_TITLE << endl;
    cout << ASCII_INSTRUCTIONS << endl;
    string user_input;
    getline(cin, user_input);
    return;
}

void GameMode::displayGameOver(PlayerID winner) {
    string winner_str;
    switch(winner) {
        case PlayerID::Player1:
            winner_str = ASCII_PLAYER_ONE;
            break;
        case PlayerID::Player2:
            winner_str = ASCII_PLAYER_TWO;
            break;
        case PlayerID::Player3:
            winner_str = ASCII_PLAYER_THREE;
            break;
        case PlayerID::Player4:
            winner_str = ASCII_PLAYER_FOUR;
            break;
        case PlayerID::Nobody:
            winner_str = ASCII_NOBODY;
            break;
    }
    cout << winner_str << endl;
    cout << ASCII_WINNER_MESSAGE_POSTFIX << endl;
}

PlayerID GameMode::runGame() {
    // Start the game with Player 1 having the first turn
    int current_player_index = 0;
    shared_ptr<Player> current_player_ptr = players[current_player_index];

    while (true) {
        // Print the board at the start of every turn
        current_player_ptr->printPlayerView(cout);

        // Conduct the current player's turn, and terminate the game with nobody winning upon EOF
        // on standard input or the 'quit' command
        if (!conductPlayerTurn(current_player_ptr)) {
            return PlayerID::Nobody;
        }

        // Go through each player to check for a winner or eliminated player
        for (int i = 0; i < num_players; ++i) {
            // Return a player if they have downloaded 4 data
            if (players[i]->getDownloadedDataAmount() >= DATA_DOWNLOADS_TO_WIN) {
                players[i]->printPlayerView(cout);
                return player_order[i];
            }
            // Remove a player from the game if they have downloaded 4 viruses (and thus lost)
            if (players[i]->getDownloadedVirusAmount() >= VIRUS_DOWNLOADS_TO_LOSE) {
                eliminated_players[i] = true;
				board->eliminatePlayer(players[i].get());
                --remaining_players;
                cout << "Player " << i + 1 << " has been eliminated!\n" << endl;
            }
        }

        // Check if all players but 1 have lost, leaving the remaining player to win
        if (remaining_players == 1) {
            for (int i = 0; i < num_players; ++i) {
                if (!eliminated_players[i]) {
                    players[i]->printPlayerView(cout);
                    return player_order[i];
                }
            }
        }

        // Change which player's turn it is
        do {
            current_player_index = (current_player_index + 1) % num_players;
        } while (eliminated_players[current_player_index]);
        current_player_ptr = players[current_player_index];
    }
}

bool GameMode::conductPlayerTurn(shared_ptr<Player> current_player_ptr) {
    bool ability_used = false;

    while (true) {
		try {
        	string line;

            // If there are no sequence files to read from, read from standard input
        	if (sequence_file.empty()) {
            	getline(cin, line);
        		if (cin.fail()) { // Terminate the game upon a failed read (i.e. EOF) from standard input
					return false;
				}
			} else { // Otherwise, read from the most current sequence file
           		getline(sequence_file.back(), line);
        		if (sequence_file.back().fail()) { // Pop back the current file if it is empty
            		sequence_file.pop_back();
            		continue;
        		}
			}

        	istringstream iss{line};
        	string cmd;
	
    	    if (!(iss >> cmd)) continue; // Skip empty lines
	
    	    // Parse the command
        	if (cmd == "abilities") {
            	current_player_ptr->displayAbility(cout);
            	continue;
	
    	    } else if (cmd == "board") {
        	    current_player_ptr->printPlayerView(cout);
            	continue;
	
    	    } else if (cmd == "ability") {
        	    if (ability_used) {
                    throw invalid_argument("An ability has already been played this turn.");
                }
            	int ability_ID;
    	        if (!(iss >> ability_ID) || ability_ID < 1 || ability_ID > 5) {
        	        throw invalid_argument("Invalid ability ID.");
        	    }
            	string ability_command;
        	    if (!getline(iss, ability_command)) {
                    throw invalid_argument("Ability command not provided.");
                }
            	current_player_ptr->usingAbility(ability_ID, ability_command);
            	ability_used = true;
            	continue;
	
    	    } else if (cmd == "move") {
        	    string move_command;
            	if (!getline(iss, move_command)) {
                    throw invalid_argument("Move command not provided.");
                }
            	current_player_ptr->movingLink(move_command);
            	return true;
	
    	    } else if (cmd == "sequence") {
        	    string sequence_file_name;
            	if (!(iss >> sequence_file_name)) {
                    throw invalid_argument("File name not provided.");
                }

                // Add the sequence file and remove it if it failed to open
	            sequence_file.emplace_back(ifstream{sequence_file_name});
    	        if (!sequence_file.back()) {
					sequence_file.pop_back();
					throw invalid_argument("File does not exist.");
				}
            	continue;
	
    	    } else if (cmd == "quit") {
        	    return false;
	
    	    } else {
        	    throw invalid_argument("Invalid command.");

        	}
		} catch (invalid_argument &e) {
			cerr << e.what() << endl;
		} catch (out_of_range &e) {
			cerr << e.what() << endl;
		} catch (...) {
			cerr << "Unknown error." << endl;
		}
    }
}
