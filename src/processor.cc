export module CommandLineProcessor;

import <iostream>;
import <string>;
import <utility>;
import <vector>;
import <stdexcept>;
import <memory>;

const int NUM_LETTERS_ALPHABET = 26;
const std::string DEFAULT_ABILITY_ORDER = "LFDSP";
const std::string AVAILABLE_ABILITIES = "LFDSPHOTU"; // All abilities must be uppercase characters (A-Z)
const int NUM_ABILITIES = 5;
const int MAX_SHARED_ABILITIES = 2;
const std::string DEFAULT_LINK_ORDER = "V1V2V3V4D1D2D3D4";
const int NUM_LINKS = 8;
const int CHARS_IN_LINK = 2;
const int LINK_SEQUENCE_LENGTH = NUM_LINKS * CHARS_IN_LINK;

struct ProcessedInput {
    std::vector<std::string> ability_orders;
    std::vector<std::string> link_orders;
    bool graphics_enabled;
};

export class final CommandLineProcessor {
    public:
        ProcessedInput processCommands(int argc, char *argv[], int player_count);
};
