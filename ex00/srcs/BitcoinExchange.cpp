/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:20 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/29 13:59:48 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <sys/stat.h>
#include <cstdio>
#include <stdlib.h>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

BitcoinExchange::BitcoinExchange(void)
{ }

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
{ }

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//

// Return a map<string, string> with database in it
static std::map<std::string, std::string> SaveFile(FILE *file)
{
	std::map<std::string, std::string> returnFile;

	char line[1024];
	while (std::fgets(line, sizeof(line), file))
	{
		std::string tmp = line;
		size_t separatorIndex = tmp.find(",");	// find separator

		// split date and amount
		std::string date = tmp.substr(0, separatorIndex);
		std::string amount = tmp.substr(separatorIndex + 1);

		std::pair<std::string, std::string> pair;
		pair.first = date;
		pair.second = amount;

		returnFile.insert(pair);
	}

	pclose(file);

	return returnFile;
}

void	BitcoinExchange::SetDataBase(std::string fileName)
{
	FILE *openFile;

	if ((openFile = MainOpenFiles(this, fileName)) == false)
	{
		std::string error = "error open files name: ";
		error += fileName;
		PrintMesg(error, T_RED, false);
	}
	_dataBase = SaveFile(openFile);
}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//

fl32	BitcoinExchange::GetChangeNbr(std::string date) const
{
	std::map<std::string, std::string>::const_iterator it = _dataBase.find(date);
	if (it != _dataBase.end()) // if key find
	{
		return atof(it->second.c_str());
	}
	else // if not find, return lower pair->second
	{
		it = _dataBase.upper_bound(date);
		it--;
		
		return atof(it->second.c_str());
	}
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

FILE	*BitcoinExchange::OpenFiles(std::string const &filename) const
{
	const char *fn = filename.c_str();
	mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // permissions 644
	int result = chmod(fn, permissions);	// change permission to 644
	
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
