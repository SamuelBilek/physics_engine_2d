CXX = g++
SRC = $(shell find src -name '*.cpp')
EXEC_NAME = physicsengine.exe

BUILD ?= debug

DIST_DIR = dist
ASSET_DIR = assets
LIBS_DIR = libs
SDL_DIR = $(LIBS_DIR)/SDL2

ifeq ($(BUILD), debug)
	DBGFLAGS = -g -O0 -DDEBUG
else ifeq ($(BUILD), release)
	DBGFLAGS = -O2 -DNDEBUG
else
	$(error Uknown build configuration: $(BUILD))
endif

CXXFLAGS = -std=c++20 -Wall -Wfatal-errors \
            $(DBGFLAGS) \
			-I$(LIBS_DIR) \
           	-I$(SDL_DIR)/include/SDL2

LDFLAGS = -L$(SDL_DIR)/lib

LDLIBS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_gfx -lSDL2

build:
	mkdir -p $(DIST_DIR)

	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) $(LDLIBS) -o $(DIST_DIR)/$(EXEC_NAME)

	cp -r $(SDL_DIR)/bin/* $(DIST_DIR)/

	mkdir -p $(DIST_DIR)/$(ASSET_DIR)
	cp -r $(ASSET_DIR)/* $(DIST_DIR)/$(ASSET_DIR)/

run:
	./$(DIST_DIR)/$(EXEC_NAME)

clean:
	rm -rf $(DIST_DIR)