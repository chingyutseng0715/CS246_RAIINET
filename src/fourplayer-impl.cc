module FourPlayerMode;

using std::string, std::cout, std::to_string, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared;

FourPlayerMode::FourPlayerMode(const ProcessedInput &input) : 
    GameMode{make_unique<FourPlayerBoard>()}, eliminated_players(NUM_PLAYERS, false) {
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, input.ability_orders[i]));
        board->addPlayer(players[i].get(), input.link_orders[i]);
    }
}

PlayerID FourPlayerMode::runGame() {
    // Start the game with Player 1 having the first turn
    int current_player_index = 0;
    PlayerID current_player = player_order[current_player_index];
    shared_ptr<Player> current_player_ptr = players[current_player_index];

    while (true) {
        bool ability_used = false;
        current_player_ptr->printPlayerView(cout);

        // Return false upon EOF or 'quit' and true upon a successful 'move'
        if (!conductPlayerTurn(current_player_ptr, ability_used)) {
            return PlayerID::Nobody;
        }

        // Return the current player if they have downloaded 4 data
        if (current_player_ptr->getDownloadedDataAmount() == 4) {
            return current_player;
        }

        // Remove the current player from if the game if they have downloaded 4 viruses
        if (current_player_ptr->getDownloadedVirusAmount() == 4) {
            eliminatedPlayers[current_player_index] = true;
            --remaining_players;
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
        } while (eliminatedPlayers[current_player_index]);
        current_player = player_order[current_player_index];
        current_player_ptr = players[current_player_index];
    }
}
