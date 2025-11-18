export module Mode;

export class Mode {
	protected:
		Board board;
		std::vector<Player> players;
	public:
		virtual void operatingGame() = 0;
		virtual ~Mode();
};
