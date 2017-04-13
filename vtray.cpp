// implement vtray main here
#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {
	if (argc == 3) {
		//opens file
		std::string jsonfname(argv[1]);
		std::ifstream ifs(jsonfname);
		if (!ifs.is_open()) {
			std::cerr << "Error: Invalid JSON file" << std::endl;
			return EXIT_FAILURE;
		}

		//output file name
		std::string outfname(argv[2]);
	}
	else if (argc == 5) {
		//checks for proper flag
		if (std::string(argv[1]) != std::string("-t")) {
			std::cerr << "Error: Invalid flag" << std::endl;
			return EXIT_FAILURE;
		}
		
		//number of threads
		int threads = strtol(argv[2], NULL, 10);

		//opens file
		std::string jsonfname(argv[3]);
		std::ifstream ifs(jsonfname);
		if (!ifs.is_open()) {
			std::cerr << "Error: Invalid JSON file" << std::endl;
			return EXIT_FAILURE;
		}

		//output file name
		std::string outfname(argv[4]);
	}
	else {
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return EXIT_FAILURE;
	}
}