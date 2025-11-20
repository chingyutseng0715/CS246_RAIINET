CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
CXXH = -std=c++20 -fmodules-ts -c -x c++-system-header

HEADERS = iostream vector map string
GCM = $(HEADERS:%=gcm.cache/usr/include/c++/14/%.gcm)
SRCS = observer.cc board.cc link.cc ability.cc player.cc link_boost.cc firewall.cc download.cc polarize.cc scan.cc mode.cc twoplayer.cc fourplayer.cc main.cc
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
