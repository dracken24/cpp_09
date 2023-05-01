/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:15:18 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/30 22:13:02 by dracken24        ###   ########.fr       */
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
	std::vector<uint32> A;
	std::vector<uint32> B;
	uint32	mid = 0;

	// std::cout << T_BLUE << "\nIN: ";
	// for (s_t i = 0; i < myVector.size(); i++)
	// {
	// 	std::cout << myVector.at(i) << " ";
	// }
	// std::cout << std::endl;


	for (s_t i = 0; i < myVector.size(); i++)
	{
		mid += myVector.at(i);
	}

	mid = mid / myVector.size();

	for (s_t i = 0; i < myVector.size(); i++)
	{
		if (myVector.at(i) > mid)
		{
			A.push_back(myVector.at(i));
		}
		else
		{
			B.push_back(myVector.at(i));
		}
	}
	// std::cout << "C" << std::endl;

	if (A.size() > 2)
	{
		A = SortNbrs(A, ++i);

		if (A.at(0) > A.at(1) && A.size() == 2)
		{
			uint32 tmp = A.at(0);
			A.at(0) = A.at(1);
			A.at(1) = tmp;
		}
	}
	if (B.size() > 2)
	{
		B = SortNbrs(B, ++i);

		if (B.at(0) > B.at(1) && B.size() == 2)
		{
			uint32 tmp = B.at(0);
			B.at(0) = B.at(1);
			B.at(1) = tmp;
		}
	}
	// std::cout << "1" << std::endl;


	// std::cout << T_GREEN << std::endl;
	// for (s_t i = 0; i < A.size(); i++)
	// {
	// 	std::cout << A.at(i) << " ";
	// }
	// std::cout << std::endl;

	// std::cout << T_MAGENTA << std::endl;
	// for (s_t i = 0; i < B.size(); i++)
	// {
	// 	std::cout << B.at(i) << " ";
	// }
	// std::cout << std::endl;




	if (A.at(0) < B.at(B.size() - 1))
	{
		for (s_t i = 0; i < B.size(); i++)
		{
			A.push_back(B.at(i));
		}

		return A;
	}
	else
	{
		for (s_t i = 0; i < A.size(); i++)
		{
			B.push_back(A.at(i));
		}

		return B;
	}

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
