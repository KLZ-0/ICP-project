# author: Adrián Kálazi (xkalaz00)

TARGET = mqtt-explorer

SRC_DIR = src
BUILD_DIR = build

BUILDFLAGS = -j 8

all: Release
.PHONY: all Release Debug doxygen pack

# TODO: LD_LIBRARY_PATH
Release Debug: cmake-gen
	cmake --build $(BUILD_DIR) --config $@ $(BUILDFLAGS)
	cmake --install $(BUILD_DIR) --config $@

cmake-gen: $(BUILD_DIR) CMakeLists.txt
	cd $< && cmake ..

$(BUILD_DIR):
	mkdir $@

run:
	./$(TARGET)

doxygen:
	doxygen Doxyfile

pack:
	echo TODO

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
