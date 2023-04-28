/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:36:23 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/27 20:57:29 by dracken24        ###   ########.fr       */
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

void	PrintMesg(std::string errorMsg, std::string color, bl8 flag)
{
	std::string error = color;
	error += errorMsg;
	
	if (flag ==true)
	{
		std::cout << error << std::endl;
	}
	else
	{
		throw std::runtime_error(error);
	}
}

bool	IsAlpha(std::string str)
{
	for (s_t i = 0; i < str.length(); i++)
	{
		if (!isalpha(str[i]))
		{
			return false;
		}
	}

	return true;
}

bl8		CheckValidDate(std::string date)
{
	// std::string year = date.substr(0, 3);
	double month = atof(date.substr(5, 6).c_str());
	double day = atof(date.substr(8, 9).c_str());
	
	// if ((date[4] | date[7]) != '-' || month >)
	// {
	// 	PrintMesg(("Error, bad date => " + date), T_RED, true);
	// }

	if (date < "2009-01-02")
	{
		PrintMesg("Error, date are befor Bitcoin start", T_RED, true);
		return false;
	}
	else if (date > "2022-03-29")
	{
		PrintMesg("Error, you are in the future", T_RED, true);
		return false;
	}
	
	return true;
}

void	ConvertBitcoin(BitcoinExchange *converter, FILE *file)
{
	bl8			skipFirst = true;
	char		line[1024];
	std::string	date;

	while (std::fgets(line, sizeof(line), file))
	{
		if (skipFirst == true)
		{
			skipFirst = false;
			continue;
		}

		std::string tmp = line;

		s_t separatorIndex = tmp.find("|"); //find separator
		
		int32 time = 0;
		for (s_t i = 0; tmp[i] != '\0'; i++)
		{
			if (tmp[i] == ' ')
				time++;
		}
		if (separatorIndex > tmp.length() || !isdigit(tmp[separatorIndex - 2]) || !isdigit(tmp[separatorIndex + 2])
			|| tmp[separatorIndex - 1] != ' ' || tmp[separatorIndex + 1] != ' ' || time != 2)
		{
			PrintMesg(("Error, bad input => " + tmp), T_RED, true);
			continue;
		}

		// Extract date and amount
		std::string date = tmp.substr(0, separatorIndex - 1);
		std::string amount = tmp.substr(separatorIndex + 2);

		if (CheckValidDate(date) == false)
		{
			continue;
		}

		double amountValue = atof(amount.c_str());
		double change = converter->GetChangeNbr(date);
		double ret;
		ret = amountValue * change;

		std::cout << T_GREEN << date << " => " <<  change << " " << ret << std::endl;
	}

	pclose(file);
}

int		main(int32 argc, char **argv)
{
	BitcoinExchange					converter;
	FILE	*openFile;

	if (argc != 2)
	{
		PrintMesg("Error, need ./bts && <file.name>", T_RED, false);
	}
	else if ((openFile = MainOpenFiles(&converter, argv[1])) == false)
	{
		std::string error = "error open files name: ";
		error += argv[1];
		PrintMesg(error, T_RED, false);
	}
	converter.SetDataBase("data.csv");
	ConvertBitcoin(&converter, openFile);

	// std::map<std::string, double>::iterator it = coinList.begin();
	// for (int i = 0; it != coinList.end(); it++)
	// {
	// 	std::string pair = it->first; // Accéder à la clé de la paire courante
	// 	std::cout << pair << " ~ ";
	// 	dbl64 nbr = it->second;
	// 	std::cout << nbr << std::endl;
	// }

	return 0;
}
