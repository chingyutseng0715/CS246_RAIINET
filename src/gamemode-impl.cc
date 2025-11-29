module GameMode;

using std::string, std::cin, std::cout, std::cerr, std::endl, std::to_string, std::ifstream, 
      std::istringstream, std::ostringstream, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared, 
      std::invalid_argument, std::out_of_range;

GameMode::GameMode(const ProcessedInput &input) : 
    num_players{input.num_players}, remaining_players{input.num_players},
    eliminated_players(input.num_players, false), graphics_enabled{input.graphics_enabled}, 
	graphic_bonus{input.graphic_bonus} {
    
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
	
	if (graphics_enabled) { // flipped graphic contruction
		windows.emplace_back(make_shared<Xwindow>());
	}
	if (graphic_bonus) { // all players graphic construction
		for (int i = 0; i < num_players; ++i) {
			windows.emplace_back(make_shared<Xwindow>());
		}
	}
}

void GameMode::refreshWindow(shared_ptr<Xwindow> window, shared_ptr<Player> player) {
	ostringstream oss;
	player->printPlayerView(oss);
	istringstream iss{oss.str()}; // record the output of the players' view
	window->clearWindow();
	int y = 50; // the start y for the output
	bool isBoard = false; // record if is now the board
	int width = window->getWidth(); // width of the font
	int height = window->getHeight(); // height of the font
	while (true) {
		string output = "";
		getline(iss, output);
		if (iss.fail()) { // output to the windows until nothing read
			break;
		}
		
		
		if (isBoard) { // color the links that are revealed or belongs to the player
			for (size_t i = 0; i < output.length(); ++i) {
				Link *link = board->getLink(output[i]);
				if (link && (link->isRevealed() || link->getPlayer() == player.get())) { // revealed or owned
					if (link->isVirus()) { // colored virus red
						window->fillRectangle(50 + i * width, y - height, width, height, Xwindow::Red);
					} else { // colored data green
						window->fillRectangle(50 + i * width, y - height, width, height, Xwindow::Green);
					}
				}
			}
		}
		window->drawString(50, y, output); 
		y += height + 2; // draw the string line by line
		if (output[0] == HORIZONTAL_BORDER_CHAR) { // check the condition of between the board
			if (isBoard) { // the border is the condition to check
				isBoard = false;
			} else {
				isBoard = true;
			}
		} 
	}
}

void GameMode::refreshPlayersWindow() {
	if (graphics_enabled) { // if we enable both kinds of graphics, the index start with 1
		for (size_t i = 1; i < windows.size(); ++i) {
			if (eliminated_players[i - 1]) continue; // skip the eliminated player since its window was closed
			refreshWindow(windows[i], players[i - 1]);
		}
	} else { // no flipped graphic emplaced before players windows
		for (size_t i = 0; i < windows.size(); ++i) {
			if (eliminated_players[i]) continue;
			refreshWindow(windows[i], players[i]);
		}
	}
}

void GameMode::operatingGame() {
    while (true) {
        PlayerID winner;
        switch (game_state) { // gameing state
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
    switch(winner) { // the winner output
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
		if (graphics_enabled) { // refresh the flipped graphics if enabled
			refreshWindow(windows[0], current_player_ptr);
		}
		
		if (graphic_bonus) { // refresh players window if enabled
			refreshPlayersWindow();
		}
        // Conduct the current player's turn, and terminate the game with nobody winning upon EOF
        // on standard input or the 'quit' command
        if (!conductPlayerTurn(current_player_ptr)) {
            return PlayerID::Nobody;
        }

        // Go through each player to check for a winner or eliminated player
        for (int i = 0; i < num_players; ++i) {
			if (eliminated_players[i]) {
				continue;
			}
            // Return a player if they have downloaded 4 data
            if (players[i]->isWin()) {
                players[i]->printPlayerView(cout);
                return player_order[i];
            }
            // Remove a player from the game if they have downloaded 4 viruses or not movable (and thus lost)
            if (players[i]->isLose()) {
                eliminated_players[i] = true;
				board->eliminatePlayer(players[i].get());
                --remaining_players;
				if (graphic_bonus) { // if player window enabled, close its window
					windows[i + graphics_enabled]->close();
				} 
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
			
			if (current_player_ptr->isWin() || current_player_ptr->isLose()) {
				return true;
			}
			
			if ((ability_used || current_player_ptr->getUsableAbilityAmount() == 0) && !current_player_ptr->movable()) {
				return true;
			}
			
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
        	    if (ability_used) { // disallow multiple play on ability
                    throw invalid_argument("An ability has already been played this turn.");
                }
            	int ability_ID;
    	        if (!(iss >> ability_ID) || current_player_ptr->getAbility(ability_ID) == nullptr) {
        	        throw invalid_argument("Invalid ability ID.");
        	    }
            	string ability_command;
        	    if (!getline(iss, ability_command)) {
                    throw invalid_argument("Ability command not provided.");
                }
            	current_player_ptr->usingAbility(ability_ID, ability_command);
            	ability_used = true;
				current_player_ptr->printPlayerView(cout);
				if (graphics_enabled) { /// refresh the windows after valid use of ability
					refreshWindow(windows[0], current_player_ptr);
				}
				if (graphic_bonus) {
					refreshPlayersWindow();
				}
            	continue;
	
    	    } else if (cmd == "move") {
        	    string move_command;
            	if (!getline(iss, move_command)) {
                    throw invalid_argument("Move command not provided.");
                }
            	current_player_ptr->movingLink(move_command); // we don't display here since it's the next turn
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
