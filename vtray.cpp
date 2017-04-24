// implement vtray main here
#include <iostream>
#include <fstream>

#include "parse.hpp"
#include "render.hpp"

int main(int argc, char * argv[]) {
	if (argc == 3) {

		JSONParse x;
		std::vector<std::unique_ptr<Object>> objects;
		//open file
		std::string jsonfname(argv[3]);
		try {
			x = JSONParse(jsonfname);
			x.parse(objects);
		}
		catch (std::exception err) {
			std::cerr << err.what() << std::endl;
			return EXIT_FAILURE;
		}

		RayTracer tr = RayTracer(x.getLights(), x.getCam());
		tr.render(objects);

		//output file name
		std::string outfname(argv[2]);
		std::cout << std::endl << outfname << std::endl;
	}
	else if (argc == 5) {
		//checks for proper flag
		if (std::string(argv[1]) != std::string("-t")) {
			std::cerr << "Error: Invalid flag" << std::endl;
			return EXIT_FAILURE;
		}
		
		//number of threads
		int threads = strtol(argv[2], NULL, 10);

		std::cout << "# threads " << threads << std::endl;

		std::vector<std::unique_ptr<Object>> objects;
		JSONParse x;
		//open file
		std::string jsonfname(argv[3]);
		try {
			x = JSONParse(jsonfname);
			x.parse(objects);
		}
		catch (std::exception err) {
			std::cerr << err.what() << std::endl;
			return EXIT_FAILURE;
		}
		
		RayTracer tr = RayTracer(x.getLights(),  x.getCam());
		tr.render(objects);

		//output file name
		std::string outfname(argv[4]);
		std::cout << std::endl << outfname << std::endl;
	}
	else {
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return EXIT_FAILURE;
	}
}