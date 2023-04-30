/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:36:23 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/29 22:40:04 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <stdlib.h>
#include <fstream>

// Open and return a file or nullptr if fail
FILE	*MainOpenFiles(BitcoinExchange *converter, std::string fileName)
{
	FILE *file = converter->OpenFiles(fileName);
	if (file)
	{
		return file;
	}

	return nullptr;
}

// Print message in std or std error with choice color
void	PrintMesg(std::string errorMsg, std::string color, bl8 flag)
{
	std::string error = color;
	error += errorMsg;
	
	if (flag == true)
	{
		std::cout << error << std::endl;
	}
	else
	{
		throw std::runtime_error(error);
	}
}

// chexl for date and amount is digit, skip . and -
bool	IsDigit(std::string str, int32 flag)
{
	bl8	dot = true;
	
	for (s_t i = 0; i < str.length(); i++)
	{
		if (flag == 1) // date, skip separator "-"
		{
			if (i == 4 || i == 7)
				continue;
		}
		if (flag == 2) // value, check if have just 1 "."
		{
			if (dot == false && str[i] == '.')
			{
				return false;
			}
			else if (str[i] == '.')
			{
				dot = false;
				continue;
			}
		}
		if (str[i] == '\n') // if touch \n at the end, return true
		{
			return true;
		}
		if (!isdigit(str[i])) // is not a digit
		{
			return false;
		}
	}

	return true;
}

// Check if is a valid date
bl8		CheckValidDate(std::string date)
{
	int32 year = (int32)atof(date.substr(0, 4).c_str());
	int32 month = (int32)atof(date.substr(5, 6).c_str());
	int32 day = (int32)atof(date.substr(8, 9).c_str());

	if ((date[4] | date[7]) != '-' || month > 12 || month < 1 || day < 1)	// check date format
	{
		PrintMesg(("Error, bad date => " + date), T_RED, true);
		return false;
	}
	else if (year % 4 == 0 && month == 2 && day > 29) // bisextile
	{
		PrintMesg(("Error, bisextile yeay, febuary over 29 day => " + date), T_RED, true);
		return false;
	}
	else // not bisextile
	{
		if (year % 4 != 0 && month == 2 && day > 28) // check febuary
		{
			PrintMesg(("Error, not bisextile yeay, febuary over 28 day => " + date), T_RED, true);
			return false;
		}
		else if (((month % 2 == 0 && month <= 7) || (month % 2 != 0 && month > 7)) && day > 30) // check 30 or 31 days in month
		{
			PrintMesg(("Error, this month can't be over 30 day => " + date), T_RED, true);
			return false;
		}
		else if (day > 31) // check if month is over 31 days
		{
			PrintMesg(("Error, this month can't be over 31 day => " + date), T_RED, true);
			return false;
		}
	}

	// check timeline
	if (date < "2009-01-02") //check if it's befor bitcoin time
	{
		PrintMesg("Error, date are befor Bitcoin start", T_RED, true);
		return false;
	}
	else if (date > "2022-03-29") // check if date is in the futur
	{
		PrintMesg("Error, you are in the future", T_RED, true);
		return false;
	}

	return true;
}

// Loop for check all line in the file
void	ConvertBitcoin(BitcoinExchange *converter, FILE *file)
{
	bl8			skipFirst = true;
	char		line[1024];
	std::string	date;

	while (std::fgets(line, sizeof(line), file))
	{
		// skip first line
		if (skipFirst == true)
		{
			skipFirst = false;
			continue;
		}

		// erase \n at the end of the string
		std::string tmp = line;
		tmp.erase(tmp.length() - 1);

		s_t separatorIndex = tmp.find("|"); //find separator
		
		// check integrity format
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

		// check if character and date is valid
		if (IsDigit(date, 1) == false || IsDigit(amount, 2) == false)
		{
			PrintMesg(("Error, date or value format not valid => " + tmp), T_RED, true);
			continue;
		}
		if (CheckValidDate(date) == false)
		{
			continue;
		}

		// convert in float for multiplication
		fl32 amountValue = static_cast<float>(atof(amount.c_str()));	// amount
		fl32 change = converter->GetChangeNbr(date);					// change rate
		fl32 ret;
		ret = amountValue * change;										// return value

		if (amountValue >= 0 && amountValue <= 1000) // Good value
		{
			std::cout << T_GREEN << date << " => " << "Amount: " << amountValue << "₿ * "
				<< "Change: " << change << " = " << ret << "$" << std::endl;
		}
		else // Bad value
		{
			PrintMesg(("Error, value (< 0) or (> 1000) => " + tmp), T_RED, true);
		}
	}

	pclose(file); // close open file
}

// Entry point
int		main(int32 argc, char **argv)
{
	BitcoinExchange					converter;
	FILE	*openFile = nullptr;

	if (argc != 2)	// check entry
	{
		PrintMesg("Error, need ./bts && <file.name>", T_RED, false);
	}
	else if ((openFile = MainOpenFiles(&converter, argv[1])) == false) // check if file is valid
	{
		std::string error = "error open files name: ";
		error += argv[1];
		PrintMesg(error, T_RED, false);
	}
	converter.SetDataBase("data.csv");		// set database in a std::map<std::string, std::string> int the class
	ConvertBitcoin(&converter, openFile);	// Loop for convert

	return 0;
}
