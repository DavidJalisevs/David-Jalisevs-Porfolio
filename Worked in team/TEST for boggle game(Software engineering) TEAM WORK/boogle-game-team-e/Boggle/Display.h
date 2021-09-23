#pragma once
#include <iostream>
#include <string>

class Display
{
public:

	std::string displayOutput(std::string t_output)
	{
		std::cout << t_output << std::endl; 
		return t_output;
	}
};

