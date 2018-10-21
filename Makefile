BUILD_DIR=build

clean:
	rm -rf $(BUILD_DIR);
build: clean
	mkdir $(BUILD_DIR);
	cd $(BUILD_DIR) && cmake .. && make;
init:
	cd $(BUILD_DIR) && chmod +x cmake_install.cmake && cmake -P cmake_install.cmake;