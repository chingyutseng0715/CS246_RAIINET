CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
CXXH = -std=c++20 -fmodules-ts -c -x c++-system-header

HEADERS = iostream sstream memory stdexcept compare vector map string
GCM = $(HEADERS:%=gcm.cache/usr/include/c++/14/%.gcm)
SRCS = observer.cc observer-impl.cc link.cc link-impl.cc board.cc board-impl.cc twoplayerboard.cc twoplayerboard-impl.cc fourplayerboard.cc ability.cc ability-impl.cc download.cc download-impl.cc firewall.cc firewall-impl.cc link-boost.cc link-boost-impl.cc scan.cc scan-impl.cc polarize.cc polarize-impl.cc player.cc player-impl.cc gamemode.cc gamemode-impl.cc twoplayer.cc twoplayer-impl.cc fourplayer.cc fourplayer-impl.cc main.cc
OBJS = $(SRCS:.cc=.o)
TARGET = RAllnet.out

all: prebuild build

prebuild:
	$(CXX) $(CXXH) $(HEADERS)

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf gcm.cache

rebuild: clean all

.PHONY: all clean rebuild
