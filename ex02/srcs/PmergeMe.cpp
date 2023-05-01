/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:15:18 by dracken24         #+#    #+#             */
/*   Updated: 2023/05/01 14:06:51 by dracken24        ###   ########.fr       */
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

	// Fill Vector and List
	for (int32 i = 1; i < argc; i++)
	{
		_myVector.push_back((uint32)atof(argv[i]));
		_myList.push_back((uint32)atof(argv[i]));
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

// Sort Vector numbers from lesser to highter
std::vector<uint32> PmergeMe::SortNbrsVector(std::vector<uint32> myVector, int i)
{
	std::vector<uint32> A;
	std::vector<uint32> B;
	uint32	mid = 0;

	// Find mid value
	for (s_t i = 0; i < myVector.size(); i++)
	{
		mid += myVector.at(i);
	}
	mid = mid / myVector.size();

	// Feel tmp array with, less than mid in B and Upper than mid in A
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

	// Recurssive SortNbrs with A and B until have less than 2 nbrs in array
	if (A.size() >= 2)
	{
		if (A.size() > 2)
			A = SortNbrsVector(A, ++i);

		// if 2 nbrs, swap nbrs if [0] is upper than [1] in A
		if (A.at(0) > A.at(1) && A.size() == 2)
		{
			uint32 tmp = A.at(0);
			A.at(0) = A.at(1);
			A.at(1) = tmp;
		}
	}
	if (B.size() >= 2)
	{
		if (B.size() > 2)
			B = SortNbrsVector(B, ++i);

		// if 2 nbrs, swap nbrs if [0] is upper than [1] in B
		if (B.at(0) > B.at(1) && B.size() == 2)
		{
			uint32 tmp = B.at(0);
			B.at(0) = B.at(1);
			B.at(1) = tmp;
		}
	}

	// If A[0] is lower than B[B.Size - 1], = (A + B)
	if (A.at(0) < B.at(B.size() - 1))
	{
		for (s_t i = 0; i < B.size(); i++)
		{
			A.push_back(B.at(i));
		}

		return A;
	}
	else // else = (B + A)
	{
		for (s_t i = 0; i < A.size(); i++)
		{
			B.push_back(A.at(i));
		}

		return B;
	}
}

void	PmergeMe::SortVectorNumbers(void)
{
	PrintVector(T_GREEN);

	struct timeval	time;
	gettimeofday(&time, NULL);
	long int start = time.tv_sec * 1000 + time.tv_usec / 1000;
	
	_myVector = SortNbrsVector(_myVector, 0);

	struct timeval time2;
	gettimeofday(&time2, NULL);
	long int end = time2.tv_sec * 1000 + time2.tv_usec / 1000;

	PrintVector(T_GREEN);
	std::cout << T_MAGENTA << "Time for std::Vector with " << _myVector.size() << " numbers : "
		<< end - start << " ms\n" << std::endl;
}

void PmergeMe::PrintVector(std::string color) const
{
	std::cout << color << "std::vector: ";
	for (s_t i = 0; i < _myVector.size(); i++)
	{
		std::cout << _myVector.at(i) << " ";
	}

	std::cout << std::endl;
}

// Sort List numbers from lesser to highter
std::list<uint32> PmergeMe::SortNbrsList(std::list<uint32> myList, int i)
{
	std::list<uint32> A;
	std::list<uint32> B;
	uint32 mid = 0;

	// Find mid value
	std::list<uint32>::const_iterator it = myList.begin();
	for (; it != myList.end(); it++)
	{
		mid += *it;
	}
	mid = mid / myList.size();

	// Feel tmp array with, less than mid in B and Upper than mid in A
	it = myList.begin();
	for (; it != myList.end(); it++)
	{
		if (*it > mid)
		{
			A.push_back(*it);
		}
		else
		{
			B.push_back(*it);
		}
	}

	// Recurssive SortNbrs with A and B until have less than 2 nbrs in array
	it = A.begin();
	if (A.size() >= 2)
	{
		if (A.size() > 2)
			A = SortNbrsList(A, ++i);

		if (*it > *++it && A.size() == 2)
		{
			--it;
			uint32 tmp = *it;
			uint32 tmp2 = *++it;

			A.clear();
			A.push_back(tmp2);
			A.push_back(tmp);
		}
	}
	it = B.begin();
	if (B.size() >= 2)
	{
		if (B.size() > 2)
			B = SortNbrsList(B, ++i);

		if (*it > *++it && B.size() == 2)
		{
			--it;
			uint32 tmp = *it;
			uint32 tmp2 = *++it;

			B.clear();
			B.push_back(tmp2);
			B.push_back(tmp);
		}
	}

	it = A.begin();
	std::list<uint32>::const_iterator it2 = B.begin();
	// If A[0] is lower than B[B.Size - 1], = (A + B)
	if (*it < *B.end())
	{
		for (s_t i = 0; i < B.size(); i++)
		{
			A.push_back(*it2);
			it2++;
		}

		return A;
	}
	else // else = (B + A)
	{
		for (s_t i = 0; i < A.size(); i++)
		{
			B.push_back(*it);
			it++;
		}

		return B;
	}
}

void	PmergeMe::SortListNumbers(void)
{
	PrintList(T_BLUE);

	struct timeval	time;
	gettimeofday(&time, NULL);
	long int start = time.tv_sec * 1000 + time.tv_usec / 1000;
	
	_myList = SortNbrsList(_myList, 0);

	struct timeval time2;
	gettimeofday(&time2, NULL);
	long int end = time2.tv_sec * 1000 + time2.tv_usec / 1000;

	PrintList(T_BLUE);
	std::cout << T_MAGENTA << "Time for std::List with " << _myList.size() << " numbers   : "
		<< end - start << " ms\n" << std::endl;
}

void	PmergeMe::PrintList(std::string color) const
{
	std::cout << color << "std::list  : ";
	
	std::list<uint32>::const_iterator it = _myList.begin();
	for (; it != _myList.end(); it++)
	{
		std::cout << *it << " ";
	}

	std::cout << std::endl;
}

// Check if argv are valid
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
		dbl64 nbr = atof(argv[i]);
		if (nbr > 4294967295) // more than a unsigned int
		{
			PrintMesg("Error, one entry is more than an unsigned int", T_RED, false);
		}
	}
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
