import <iostream>;
import <stdexcept>;
import GameMode;
import CommandLineProcessor;

int main(int argc, char *argv[]) {
	try {
		ProcessedInput input = processCommands(argc, argv);
		GameMode RAIInet(input);
		RAIInet.operatingGame();
	} catch (std::invalid_argument &e) {
		std::cerr << e.what() << '\n';
	} catch (...) {
		std::cerr << "Error occurs. Program terminates.\n";
	}
}
