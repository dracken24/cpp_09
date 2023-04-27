/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:36:23 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/26 19:48:50 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <stdlib.h>
#include <fstream>

FILE	*MainOpenFiles(BitcoinExchange *converter, std::string fileName)
{
	FILE *file = converter->OpenFiles(fileName);
	if (file)
	{
		return file;
	}

	return nullptr;
}

void	PrintError(std::string errorMsg, std::string color)
{
	std::string error = color;
	error += errorMsg;
	throw std::runtime_error(error);
}

bool	IsAlpha(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isalpha(str[i]))
		{
			return false;
		}
	}

	return true;
}

std::map<std::string, double> SaveFile(FILE *file)
{
	std::map<std::string, double> returnFile;

	bl8		skipFirst = true;
	char	line[1024];
	while (std::fgets(line, sizeof(line), file))
	{
		if (skipFirst == true)
		{
			skipFirst = false;
			continue;
		}
		// std::cout << line;
		std::string tmp = line;

		size_t separatorIndex = tmp.find("|");
		// std::cout << separatorIndex << std::endl;
		if (separatorIndex > tmp.length())
		{
			// double amountValue;
			std::pair<std::string, double> pair;
			pair.first = tmp;
			// pair.second = amountValue;

			returnFile.insert(pair);
			continue;
		}

		// Extraire la date et le montant en utilisant la fonction substr()
		std::string date = tmp.substr(0, separatorIndex - 1);
		std::string amount = tmp.substr(separatorIndex + 2);

		double amountValue = atof(amount.c_str());
		
		// std::pair<std::string, double> pair;
		// pair.first = date;
		// pair.second = amountValue;

		// returnFile.insert(pair);
	}

	pclose(file);

	return returnFile;
}

int		main(int argc, char **argv)
{
	std::map<std::string, double>	coinList;
	BitcoinExchange					converter;
	FILE	*openFile;

	if (argc != 2)
	{
		PrintError("Error, need ./bts && <file.name>", T_RED);
	}
	else if ((openFile = MainOpenFiles(&converter, argv[1])) == false)
	{
		std::string error = "error open files name: ";
		error += argv[1];
		PrintError(error, T_RED);
	}
	converter.SetDataBase("data.csv");
	coinList = SaveFile(openFile);

	// std::map<std::string, double>::iterator it = coinList.begin();
	// for (int i = 0; it != coinList.end(); it++)
	// {
	// 	std::string pair = it->first; // Accéder à la clé de la paire courante
	// 	std::cout << pair << " ~ ";
	// 	dbl64 nbr = it->second;
	// 	std::cout << nbr << std::endl;
	// }

	// std::cout << argv[1] << std::endl;
	
	return 0;
}
