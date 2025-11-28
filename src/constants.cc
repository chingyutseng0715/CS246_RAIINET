export module Constants;

import <string>;

export const int TWO_PLAYER_NUM = 2;
export const int FOUR_PLAYER_NUM = 4;

export const int DATA_DOWNLOADS_TO_WIN = 4;
export const int VIRUS_DOWNLOADS_TO_LOSE = 4;

export const std::string DEFAULT_ABILITY_ORDER = "LFDSP";
export const std::string AVAILABLE_ABILITIES = "LFDSPHOTU";
export const int ABILITIES_PER_PLAYER = 5;
export const int MAX_SHARED_ABILITIES = 2;
export const int NUM_LETTERS_ALPHABET = 26;

export const std::string DEFAULT_LINK_ORDER = "V1V2V3V4D1D2D3D4";
export const int LINKS_PER_PLAYER = 8;
export const int CHARS_IN_LINK = 2;
export const int LINK_SEQUENCE_LENGTH = LINKS_PER_PLAYER * CHARS_IN_LINK;

export const bool DEFAULT_GRAPHICS_SETTING = false;

export const std::string PLAYER_NAME_PREFIX = "Player ";
export const std::string PLAYER1 = "Player 1";
export const std::string PLAYER2 = "Player 2";
export const std::string PLAYER3 = "Player 3";
export const std::string PLAYER4 = "Player 4";

export const int BOARD_HEIGHT = 10;
export const int TWO_PLAYER_BOARD_WIDTH = 8;
export const int FOUR_PLAYER_BOARD_WIDTH = 16;

export const char DATA_CHAR = 'D';
export const char VIRUS_CHAR = 'V';
export const char HORIZONTAL_BORDER_CHAR = '=';
export const char EMPTY_SQUARE_CHAR = '.';
export const char SERVER_PORT_CHAR = 'S';
export const char UNREVEALED_LINK_CHAR = '?';
export const char PLAYER1_FIREWALL = 'x';
export const char PLAYER2_FIREWALL = 'y';
export const char PLAYER3_FIREWALL = 'z';
export const char PLAYER4_FIREWALL = 'w';
export const char OBSTACLE_CHAR = '#';

export const char DEFAULT_STEPS_PER_MOVE = 1;

export const char NULL_ABILITY = '#';
