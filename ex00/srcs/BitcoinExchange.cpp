/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:20 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/26 20:18:36 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

BitcoinExchange::BitcoinExchange(void)
{

}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &copy)
{
	if (this != &copy)
	{
		_dataBase = copy._dataBase;
	}

	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
	
}

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//

static std::map<std::string, double>	SaveFile(FILE *file)
{
	std::map<std::string, double> returnFile;

	bl8 skipFirst = true;
	char line[1024];
	while (std::fgets(line, sizeof(line), file))
	{
		if (skipFirst == true)
		{
			skipFirst = false;
			continue;
		}
		std::string tmp = line;

		size_t separatorIndex = tmp.find(",");

		// Extract date ans amount with substr()
		std::string date = tmp.substr(0, separatorIndex);
		std::string amount = tmp.substr(separatorIndex + 1);

		double amountValue = atof(amount.c_str());

		std::pair<std::string, double> pair;
		pair.first = date;
		pair.second = amountValue;

		returnFile.insert(pair);
	}

	pclose(file);

	// std::map<std::string, double>::iterator it = returnFile.begin();
	// for (int i = 0; it != returnFile.end(); it++)
	// {
	// 	std::string pair = it->first; // Accéder à la clé de la paire courante
	// 	std::cout << pair << " ~ ";
	// 	dbl64 nbr = it->second;
	// 	printf("%.2f\n", nbr);
	// }

	return returnFile;
}

void	BitcoinExchange::SetDataBase(std::string fileName)
{
	FILE *openFile;
	// file = OpenFiles(fileName);
	if ((openFile = MainOpenFiles(this, fileName)) == false)
	{
		std::string error = "error open files name: ";
		error += fileName;
		PrintError(error, T_RED);
	}
	SaveFile(openFile);
}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//



//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

FILE	*BitcoinExchange::OpenFiles(std::string const &filename) const
{
	const char *fn = filename.c_str();
	mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // permissions 644
	int result = chmod(fn, permissions);
	if (result == 0)
	{
		FILE *file = fopen(filename.c_str(), "r");
		if (file == nullptr)
		{
			throw std::runtime_error("Unable to open configuration file " + filename);
		}
		return file;
	}
	
	return nullptr;
}