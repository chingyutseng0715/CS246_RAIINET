export module CommandLineProcessor;

import <iostream>;
import <string>;
import <utility>;
import <vector>;
import <stdexcept>;
import <memory>;

const std::string DEFAULT_ABILITY_ORDER = "LFDSP";
const std::string AVAILABLE_ABILITIES = "LFDSPHOTU"; // All abilities must be uppercase characters (A-Z)
const int ABILITIES_PER_PLAYER = 5;
const int MAX_SHARED_ABILITIES = 2;
const int NUM_LETTERS_ALPHABET = 26;

const std::string DEFAULT_LINK_ORDER = "V1V2V3V4D1D2D3D4";
const int LINKS_PER_PLAYER = 8;
const int CHARS_IN_LINK = 2;
const int LINK_SEQUENCE_LENGTH = LINKS_PER_PLAYER * CHARS_IN_LINK;

struct ProcessedInput {
    std::vector<std::string> ability_orders;
    std::vector<std::string> link_orders;
    bool graphics_enabled;
};

export ProcessedInput processCommands(int argc, char *argv[], int player_count);
