# author: Adrián Kálazi (xkalaz00)

TARGET = mqtt-explorer
ZIPFILE = 1-xkalaz00-xlacko08.zip

SRC_DIR = src
BUILD_DIR = build

BUILDFLAGS = -j 8

all: Release
.PHONY: all Release Debug doxygen pack

Release Debug: $(BUILD_DIR) CMakeLists.txt
	cd $< && cmake -DCMAKE_BUILD_TYPE=$@ ..
	cmake --build $(BUILD_DIR) --config $@ $(BUILDFLAGS)
	cmake --install $(BUILD_DIR) --config $@

$(BUILD_DIR):
	mkdir $@

run:
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib/:/usr/local/share/Qt-5.5.1/ && ./$(TARGET)

doxygen:
	doxygen Doxyfile

pack:
	zip -r $(ZIPFILE) src examples
	zip $(ZIPFILE) doc README.txt Makefile CMakeLists.txt Doxyfile

clean-pack:
	rm -f $(ZIPFILE)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
