module CommandLineProcessor;

using std::string, std::to_string, std::stoi, std::move, std::invalid_argument, std::vector;

ProcessedInput processCommands(int argc, char* argv[]) {
    ProcessedInput processed;
    int player_count = TWO_PLAYER_NUM;
    int first_potential_command_pos = 1;

    if (argc == 1) {
        return {player_count, vector<string>(player_count, DEFAULT_ABILITY_ORDER), 
                vector<string>(player_count, DEFAULT_LINK_ORDER), false};
    }

    if (string(argv[1]) == "-players") {
        if (argc <= 2) throw invalid_argument("Player count not provided.");
        player_count = stoi(argv[2]);
        if (player_count != TWO_PLAYER_NUM && player_count != FOUR_PLAYER_NUM) {
            throw invalid_argument("Must be either 2 players or 4 players.");
        }

        first_potential_command_pos += 2;
    }
    
    vector<string> ability_orders(player_count, DEFAULT_ABILITY_ORDER);
    vector<string> link_orders(player_count, DEFAULT_LINK_ORDER);
    vector<bool> ability_order_set(player_count, false);
    vector<bool> link_order_set(player_count, false);
	bool graphics_set = false;
    
	for (int i = first_potential_command_pos; i < argc; ++i) {
        bool ordering_command_provided = false;

        for (int j = 0; j < player_count; ++j) {
            if (string(argv[i]) == "-ability" + to_string(j + 1) && !ability_order_set[j]) {
                if (argc <= i + 1) throw invalid_argument("Ordering not provided.");

                string ability_order = string(argv[i + 1]);
                if (ability_order.length() != ABILITIES_PER_PLAYER) {
                    throw invalid_argument("Invalid number of abilities.");
                }
                
                int char_frequency[NUM_LETTERS_ALPHABET] = {0};
                for (char ability : ability_order) {
                    if (AVAILABLE_ABILITIES.find(ability) == AVAILABLE_ABILITIES.npos) {
                        throw invalid_argument("Listed ability does not exist.");
                    }
                    if ((++char_frequency[ability - 'A']) > MAX_SHARED_ABILITIES) {
                        throw invalid_argument("Same ability selected more than twice.");
                    }
                }

                ability_orders[j] = ability_order;
                ability_order_set[j] = true;
                ordering_command_provided = true;
                ++i;
                break;
            }

            if (string(argv[i]) == "-link" + to_string(j + 1) && !link_order_set[j]) {
                if (argc <= i + 1) throw invalid_argument("Ordering not provided.");

                string link_order = string(argv[i + 1]);
                if (link_order.length() != LINK_SEQUENCE_LENGTH) {
                    throw invalid_argument("Invalid link sequence length.");
                }

                vector<string> listed_links;
                for (int k = 0; k < LINK_SEQUENCE_LENGTH; k += CHARS_IN_LINK) {
                    string current_link = link_order.substr(k, CHARS_IN_LINK);
                    if (DEFAULT_LINK_ORDER.find(current_link) == DEFAULT_LINK_ORDER.npos) {
                        throw invalid_argument("Listed link does not exist.");
                    }
                    if (find(listed_links.begin(), listed_links.end(), current_link) != listed_links.end()) {
                        throw invalid_argument("Same link selected more than once.");
                    }
                    listed_links.emplace_back(current_link);
                }

                link_orders[j] = link_order;
                link_order_set[j] = true;
                ordering_command_provided = true;
                ++i;
                break;
            }

        }
        
        if (ordering_command_provided) continue;

        if (string(argv[i]) == "-graphics" && !graphics_set) {
			// Code to enable graphics to be added (maybe)
			graphics_set = true;
            continue;
		}
        
        throw invalid_argument("Invalid command-line arguments.");
	}

    processed.num_players = player_count;
    processed.ability_orders = move(ability_orders);
    processed.link_orders = move(link_orders);
    processed.graphics_enabled = graphics_set;
    return processed;
}
