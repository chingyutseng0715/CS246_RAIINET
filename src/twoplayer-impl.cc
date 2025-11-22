module TwoPlayerMode;

const std::string PLAYER1 = "Player 1";
const std::string PLAYER2 = "Player 2";

TwoPlayerMode::TwoPlayerMode(std::string ability1_order, std::string ability2_order, 
                             std::string link1_order, std::string link2_order) : 
    GameMode{std::make_shared<TwoPlayerBoard>()} {
    ability_orders.emplace_back(ability1_order);
    ability_orders.emplace_back(ability2_order);
    link_orders.emplace_back(link1_order);
    link_orders.emplace_back(link2_order);
    players.emplace_back(std::make_shared<Player>(PLAYER1, board, ability_orders[0]));
    players.emplace_back(std::make_shared<Player>(PLAYER2, board, ability_orders[1]));
    
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        board->addPlayer(players[i], link_orders[i]);
    }
}

void TwoPlayerMode::runGame() {
    while (true) {
        
    }
}
