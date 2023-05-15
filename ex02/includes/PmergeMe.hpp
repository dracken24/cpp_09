/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:08:21 by dracken24         #+#    #+#             */
/*   Updated: 2023/05/15 13:13:44 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>

# define true 1
# define false 0
# define s_t size_t

# ifndef nullptr
#  define nullptr NULL
# endif

# define T_BLACK "\033[30m"
# define T_RED "\033[31m"
# define T_GREEN "\033[32m"
# define T_YELLOW "\033[33m"
# define T_BLUE "\033[36m"
# define T_MAGENTA "\033[35m"
# define T_CYAN "\033[34m"
# define T_WHITE "\033[37m"
# define T_RESET "\033[0m"

// int
typedef int int32;

// Unsigned int types.
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed int types.
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef signed long long sint64;

// Floating point types
typedef float fl32;
typedef double dbl64;

// Boolean types
typedef char bl8;

class PmergeMe
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		PmergeMe(void);
		~PmergeMe(void);
		PmergeMe(PmergeMe const &copy);
		PmergeMe	&operator=(PmergeMe const &copy);

	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//

		void	SetContainers(int32 argc, char **argv);

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		void				PrintMesg(std::string errorMsg, std::string color, bl8 flag) const;
		void				SortVectorNumbers(void);
		void				SortListNumbers(void);
		void				PrintVector(std::string color) const;
		void				PrintList(std::string color) const;

	private:
		std::vector<uint32>	SortNbrsVector(std::vector<uint32> myVector, int32 i);
		std::list<uint32>	SortNbrsList(std::list<uint32> myVector, int32 i);
		void				CheckEntry(int32 argc, char **argv); 

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private:
		std::vector<uint32>	_myVector;
		std::list<uint32>	_myList;
};

#endif
