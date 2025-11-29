export module CommandLineProcessor;

import <iostream>;
import <string>;
import <utility>;
import <algorithm>;
import <vector>;
import <stdexcept>;
import Constants;

export struct ProcessedInput {
    int num_players;
    std::vector<std::string> ability_orders;
    std::vector<std::string> link_orders;
    bool graphics_enabled;
	bool graphic_bonus;
};

// processCommands(argc, argv) Processes all command-line arguments and return them as a
//   ProcessedInput. Use default values for options with flags not provided.
export ProcessedInput processCommands(int argc, char *argv[]);
