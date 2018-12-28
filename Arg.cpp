#include "Arg.h"

Arg::Arg(int count, char **args) {
	std::string tmp;
	this->error = false;
	for (int i = 1; i < count; i++) {
		tmp = readLine(args[i]);
		switch (i) {
		case 1:
			if (tmp == "e") {
				g=1;
			}
			else if (tmp == "d") {
				g=0;
			}
			break;
		case 2:
			input = tmp;
			break;
		case 3:
			output = tmp;
			break;
		default:
			error = true;
			break;
		}
		if (error) break;
	}
}

std::string Arg::readLine(char *line) {
	std::string tmp = "";
	for (int i = 0; line[i] != 0; i++) {
		tmp += line[i];
	}
	return tmp;
}