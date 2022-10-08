
#include "MyFramework.h"
#include <string>
#include <vector>
#include <sstream>

char* getParam(char** first, char** last, const std::string& parameter)
{
	char** itr = std::find(first, last, parameter);
	if (itr != last && itr++ != last)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char** first, char** last, const std::string& parameter)
{
	return std::find(first, last, parameter) != last;
}

int main(int argc, char* argv[])
{
	int w = 800;
	int h = 600;

	if (argc >= 3 && cmdOptionExists(argv, argv + argc, "-window"))
	{
		char* parameter = getParam(argv, argv + argc, "-window");
		printf("-window value = %s\n", parameter);

		std::stringstream stringParameter(parameter);
		std::string segment;
		std::vector<std::string> seglist;
		while (std::getline(stringParameter, segment, 'x'))
		{
			seglist.push_back(segment);
		}

		if (seglist.size() >= 2)
		{
			w = stoi(seglist[0]);
			h = stoi(seglist[1]);
		}
	}
	/*printf("argc = %d\n", argc);
	printf("argv = %s\n", argv[1]);
	printf("argv = %s\n", argv[2]);*/
	return run(new MyFramework(w, h));
}


