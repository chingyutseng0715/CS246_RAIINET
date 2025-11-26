export module Constants;

import <string>;

export const int TWO_PLAYER_NUM = 2;
export const int FOUR_PLAYER_NUM = 4;

export const int DATA_DOWNLOADS_TO_WIN = 4;
export const int VIRUS_DOWNLOADS_TO_LOSE = 4;

export const std::string DEFAULT_ABILITY_ORDER = "LFDSP";
export const std::string AVAILABLE_ABILITIES = "LFDSPHOTU"; // All ability indicators must 
                                                            // be uppercase characters (A-Z)
export const int ABILITIES_PER_PLAYER = 5;
export const int MAX_SHARED_ABILITIES = 2;
export const int NUM_LETTERS_ALPHABET = 26;

export const std::string DEFAULT_LINK_ORDER = "V1V2V3V4D1D2D3D4";
export const int LINKS_PER_PLAYER = 8;
export const int CHARS_IN_LINK = 2;
export const int LINK_SEQUENCE_LENGTH = LINKS_PER_PLAYER * CHARS_IN_LINK;

export const std::string PLAYER1 = "Player 1";
export const std::string PLAYER2 = "Player 2";
export const std::string PLAYER3 = "Player 3";
export const std::string PLAYER4 = "Player 4";

export const int BOARD_HEIGHT = 10;
export const int TWO_PLAYER_BOARD_WIDTH = 8;
export const int FOUR_PLAYER_BOARD_WIDTH = 16;

export const char SERVER_PORT_CHAR = 'S';
