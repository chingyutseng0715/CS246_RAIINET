module FourPlayerMode;

using std::string, std::cout, std::endl, std::to_string, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared;

FourPlayerMode::FourPlayerMode(const ProcessedInput &input) : 
    GameMode{make_unique<FourPlayerBoard>()}, eliminated_players(NUM_PLAYERS, false) {
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board.get(), input.ability_orders[i]));
        board->addPlayer(players[i].get(), input.link_orders[i]);
    }
}

PlayerID FourPlayerMode::runGame() {
    // Start the game with Player 1 having the first turn
    int current_player_index = 0;
    shared_ptr<Player> current_player_ptr = players[current_player_index];

    while (true) {
        bool ability_used = false;
        current_player_ptr->printPlayerView(cout);

        // Return false upon EOF or 'quit' and true upon a successful 'move'
        if (!conductPlayerTurn(current_player_ptr, ability_used)) {
            return PlayerID::Nobody;
        }

        for (int i = 0; i < NUM_PLAYERS; ++i) {
            // Return a player if they have downloaded 4 data
            if (players[i]->getDownloadedDataAmount() == DATA_DOWNLOADS_TO_WIN) {
                players[i]->printPlayerView(cout);
                return player_order[current_player_index];
            }
            // Remove a player from the game if they have downloaded 4 viruses (and thus lost)
            if (players[i]->getDownloadedVirusAmount() == VIRUS_DOWNLOADS_TO_LOSE) {
                eliminated_players[i] = true;
                --remaining_players;
                cout << "Player " << i + 1 << " has been eliminated!\n" << endl;
            }
        }

        // Check if 3 players have lost, leaving the last player to win
        if (remaining_players == 1) {
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                if (!eliminated_players[i]) return player_order[i];
            }
        }

        // Change which player's turn it is
        do {
            current_player_index = (current_player_index + 1) % NUM_PLAYERS;
        } while (eliminated_players[current_player_index]);
        current_player_ptr = players[current_player_index];
    }
}
