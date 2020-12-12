
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;


vector<char>& leerDatos (const char *src)
 {
	std::fstream input;
	  vector<char> *output = new vector<char> ();

	input.open (src, std::fstream::in);
	if (!input) return *output;

while (true)
{
	char ch = input.get();
	if (input.eof()) break;

	output->push_back(ch);
}

	input.close();
	return *output;
}
