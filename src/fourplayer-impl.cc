module FourPlayerMode;

using std::string, std::shared_ptr, std::make_shared, std::ifstream, std::invalid_argument;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";
const std::string PLAYER3 = "Player 3";
const std::string PLAYER4 = "Player 4";

FourPlayerMode::FourPlayerMode(const ProcessedInput &input) : 
    GameMode{make_shared<FourPlayerBoard>()} {
    ability_orders = input.ability_orders;
    link_orders = input.link_orders;
    players.emplace_back(make_shared<Player>(PLAYER1, board, ability_orders[0]));
    players.emplace_back(make_shared<Player>(PLAYER2, board, ability_orders[1]));
    players.emplace_back(make_shared<Player>(PLAYER3, board, ability_orders[2]));
    players.emplace_back(make_shared<Player>(PLAYER4, board, ability_orders[3]));

    for (int i = 0; i < NUM_PLAYERS; ++i) {
        // players.emplace_back(make_shared<Player>("Player " + to_string(i + 1), board, ability_orders[i]));
        board->addPlayer(players[i], link_orders[i]);
    }
}

void FourPlayerMode::runGame() {

}
