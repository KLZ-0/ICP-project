# author: Adrián Kálazi (xkalaz00)

SRC_DIR = src
BUILD_DIR = build

BUILDFLAGS = -j 8

all: Release
.PHONY: all Release Debug

Release Debug: cmake-gen
	cmake --build $(BUILD_DIR) --config $@ $(BUILDFLAGS)
	cmake --install $(BUILD_DIR) --config $@

cmake-gen: $(BUILD_DIR) CMakeLists.txt
	cd $< && cmake ..

$(BUILD_DIR):
	mkdir $@

doxygen:
	echo TODO

clean:
	rm -rf $(BUILD_DIR)
