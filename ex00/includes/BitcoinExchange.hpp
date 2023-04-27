/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:43:35 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/26 19:47:08 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <cstring>
# include <map>
# include <string>

# define true 1
# define false 0
# define nullptr NULL
# define s_t size_t

# define T_BLACK "\033[30m"
# define T_RED "\033[31m"
# define T_GREEN "\033[32m"
# define T_YELLOW "\033[33m"
# define T_BLUE "\033[36m"
# define T_MAGENTA "\033[35m"
# define T_CYAN "\033[34m"
# define T_WHITE "\033[37m"

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

class BitcoinExchange
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		
		BitcoinExchange(BitcoinExchange const &copy);
		BitcoinExchange &operator=(BitcoinExchange const &copy);

	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//

		void	SetDataBase(std::string fileName);

	//**********************************************************************//
	//**                     		GETTERS    	     		              **//
	//**********************************************************************//



	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

		FILE	*OpenFiles(std::string const &filename) const;

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private:
		std::map<std::string, double>	_dataBase;
};

FILE	*MainOpenFiles(BitcoinExchange *converter, std::string fileName);
void	PrintError(std::string errorMsg, std::string color);

#endif

