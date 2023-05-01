/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:15:18 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/30 21:01:32 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

#include <cstdlib>
#include <cstring>
#include <sys/time.h>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//
PmergeMe::PmergeMe(void)
{
	
}

PmergeMe::~PmergeMe(void)
{
	
}

PmergeMe::PmergeMe(PmergeMe const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

PmergeMe &PmergeMe::operator=(PmergeMe const &copy)
{
	if (this != &copy)
	{
		_myVector = copy._myVector;
		_myList = copy._myList;
	}

	return *this;
}

//**********************************************************************//
//**                     		SETTERS    	     		              **//
//**********************************************************************//

void	PmergeMe::SetContainers(int32 argc, char **argv)
{
	CheckEntry(argc, argv);

	for (int32 i = 1; i < argc; i++)
	{
		_myVector.push_back((uint32)atof(argv[i]));
	}
}

//**********************************************************************//
//**                     		GETTERS    	     		              **//
//**********************************************************************//

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

static bool	IsDigit(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}

	return true;
}

// Sort numbers from lesser to highter
std::vector<uint32> PmergeMe::SortNbrs(std::vector<uint32> myVector, int i)
{
		if (myVector.size() > 2)
		{
			std::vector<uint32> tmp;
			for (s_t k = 0; k < myVector.size() / 2; k++)
			{
				tmp.push_back(myVector.at(k));
				myVector.erase(myVector.begin() + k);
			}
			tmp = SortNbrs(tmp, ++i);
			for (s_t k = tmp.size(); k > 0; k--)
			{
				myVector.push_back(tmp.at(k - 1));
			}
		}
		if (myVector.size() == 1)
		{
			return myVector;
		}


		if (myVector.at(0) > myVector.at(1) && myVector.size() > 1)
		{
			uint32 tmp = myVector.at(0);
			myVector.at(0) = myVector.at(1);
			myVector.at(1) = tmp;
		}
		// if (myVector.size() > 2)
		// {
		// 	PrintContainers();

		// 	for (s_t k = 0; k < myVector.size(); k++)
		// 	{
		// 		for (s_t g = k + 1; g < myVector.size(); g++)
		// 		{
		// 			// std::cout << T_CYAN;
		// 			// for (s_t i = 0; i < myVector.size(); i++)
		// 			// {
		// 			// 	std::cout << myVector.at(i) << " ";
		// 			// }
		// 			// std::cout << std::endl;
					
		// 			if (g == k)
		// 			{
		// 				continue;
		// 			}
		// 			if (myVector.at(k) > myVector.at(g))
		// 			{
		// 				// std::cout << "SWAP" << std::endl;
		// 				uint32 tmp = myVector.at(k);
		// 				myVector.at(k) = myVector.at(g);
		// 				myVector.at(g) = tmp;
						
		// 				// std::cout << T_BLUE;
		// 				// for (s_t i = 0; i < myVector.size(); i++)
		// 				// {
		// 				// 	std::cout << myVector.at(i) << " ";
		// 				// }
		// 				// std::cout << std::endl;
		// 			}
		// 		}
		// 	}
		// }
		return myVector;
}

void	PmergeMe::SortNumbers(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	long int start = time.tv_sec * 1000 + time.tv_usec / 1000;
	
	_myVector = SortNbrs(_myVector, 0);

	struct timeval time2;
	gettimeofday(&time2, NULL);
	long int end = time2.tv_sec * 1000 + time2.tv_usec / 1000;
	std::cout << T_GREEN << "Time for std::Vector: " << end - start << " ms" << std::endl;
}

// Print message in std or std error with choice color
void	PmergeMe::PrintMesg(std::string errorMsg, std::string color, bl8 flag) const
{
	std::string error = color;
	error += errorMsg;
	
	if (flag == true)
	{
		std::cout << error << std::endl;
	}
	else
	{
		std::cerr << error << std::endl;
		exit(-1);
	}
}

void	PmergeMe::PrintContainers(void) const
{
	for (s_t i = 0; i < _myVector.size(); i++)
	{
		std::cout << _myVector.at(i) << " ";
	}
	
	std::cout << std::endl;
}

void	PmergeMe::CheckEntry(int32 argc, char **argv)
{
	for (int32 i = 1; i < argc; i++)
	{
		if (std::strchr(argv[i], '-')) // check for negative nbrs
		{
			PrintMesg("Error, numbers can't be negatives", T_RED, false);
		}
		if (IsDigit(argv[i]) == false)
		{
			PrintMesg("Error, entry must be digit", T_RED, false);
		}
	}
}
