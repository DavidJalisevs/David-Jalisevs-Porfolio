#pragma once
#include <iostream>
class WordChecker
{
public:
	std::string wordCheck(std::string t_input, char t_letterArray[16])
	{
		int i = 0;
		std::string m_presetWords[25] = { "aidful","blog","dog","fog","god","modify","toy","aid","ufo","fluid","golf","idol","log","try","flu","tog","lot","dry","tom","mod","got","dot","tod","clog","codify" };

		for (i; i < 25; i++)
		{
			if (m_presetWords[i] == t_input)
			{
				return m_presetWords[i];
			}
		}

		return "";

	}

};