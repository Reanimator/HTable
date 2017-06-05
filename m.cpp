#include "Hastable.h"
#include <iostream>
#include <string>

void main()
{
	Table<int,std::string> t(50);
	for (int i = 0; i < 3; i++)
		t.input();

	std::cout << t[15] << std::endl;
	std::cout << t[37] << std::endl;
	std::cout << t[49] << std::endl;
	std::cout << t[41] << std::endl;

	std::cin.get();

}