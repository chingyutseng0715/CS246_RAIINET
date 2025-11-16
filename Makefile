CXX = g++-14 -std=c++20 -fmodules-ts -Wall -g
CXXH = g++-14 -std=c++20 -fmodules-ts -c -x c++-system-header
TARGET = RAIINET

$(TARGET): 
	$(CXXH) iostream utility algorithm vector sstream string
	$(CXX) -c 
	$(CXX)  $(TARGET)

clean:
	rm -f *.o $(TARGET)
	rm -rf gcm.cache
	