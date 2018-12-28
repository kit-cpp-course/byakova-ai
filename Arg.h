#ifndef IDEA_ARG_H
#define IDEA_ARG_H

#include <string>

/* parsing command line arguments */
class Arg {

public:
	Arg(int count, char** args);
	std::string readLine(char* line);
	std::string pass, input, output;
	bool error;
	int g;
};


#endif