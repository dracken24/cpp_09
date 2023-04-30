/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:03:03 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/30 00:56:39 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

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
typedef fl32 dbl64;

// Boolean types
typedef char bl8;

class RPN
{
	//**********************************************************************//
	//**                     Constructors / Destructor                    **//
	//**********************************************************************//
	public:
		RPN(std::string equation, int32 nbr);
		~RPN(void);
		RPN(RPN const &copy);
		RPN	&operator=(RPN const &copy);

	private:
		RPN(void);

	//**********************************************************************//
	//**                     		SETTERS    	     		              **//
	//**********************************************************************//

	//**********************************************************************//
	//**                     		GETTERS    	     		              **//
	//**********************************************************************//

	//**********************************************************************//
	//**                          PUBLIC METHODS                          **//
	//**********************************************************************//

	//**********************************************************************//
	//**                          MEMBERS VARS	                          **//
	//**********************************************************************//
	private:
		std::stack<int32>	_equation;
};

#endif
