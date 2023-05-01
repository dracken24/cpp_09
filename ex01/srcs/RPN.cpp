/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:03:00 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/30 17:22:19 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

#include <sstream>
#include <cstdlib>

//**********************************************************************//
//**                     Constructors / Destructor                    **//
//**********************************************************************//

RPN::RPN(void)
{ }

RPN::~RPN(void)
{ }

RPN::RPN(RPN const &copy)
{
	if (this != &copy)
	{
		*this = copy;
	}
}

RPN &RPN::operator=(RPN const &copy)
{
	if (this != &copy)
	{
		_stack = copy._stack;
	}

	return *this;
}

//**********************************************************************//
//**                          PUBLIC METHODS                          **//
//**********************************************************************//

int32   RPN::CalculRpn(const std::string &rpnExpression)
{
	CheckEntry(rpnExpression);

	std::istringstream charByChar(rpnExpression);
	int32 result = 0;
	std::string token;

	while (charByChar >> token)
	{
		if (token == "+")
		{
			int32 nbr1 = _stack.top();
			_stack.pop();
			int32 nbr2 = _stack.top();
			_stack.pop();
			
			result = nbr2 + nbr1;
			_stack.push(result);
		}
		else if (token == "-")
		{
			int32 nbr1 = _stack.top();
			_stack.pop();
			int32 nbr2 = _stack.top();
			_stack.pop();
			
			result = nbr2 - nbr1;
			_stack.push(result);
		}
		else if (token == "*")
		{
			int32 nbr1 = _stack.top();
			_stack.pop();
			int32 nbr2 = _stack.top();
			_stack.pop();

			result = nbr2 * nbr1;
			_stack.push(result);
		}
		else if (token == "/")
		{
			int32 nbr1 = _stack.top();
			_stack.pop();
			int32 nbr2 = _stack.top();
			_stack.pop();
			
			result = nbr2 / nbr1;
			_stack.push(result);
		}
		else
		{
			int32 operand = (int32)atof(token.c_str());
			_stack.push(operand);
		}
	}

	return _stack.top();
}

static bl8	CheckSign(char sign)
{
	if (sign == '+' || sign == '-' || sign == '/' || sign == '*')
	{
		return true;
	}

	return false;
}

void	RPN::CheckEntry(std::string expression)
{
	std::string ret = "Error, invalid format, your input :" + expression + "\n";
	ret += "Valid format ex.: (4 7 + 8 * 2 - 3 /)";

	for (s_t i = 0; i < expression.size(); i++)
	{
		if (i % 2 == 0)
		{
			if (i < 4) // check 2 first nbrs
			{
				if (isdigit(expression[i]) == false)
				{
					PrintMesg(ret, T_RED, false);
				}
			}
			else if (i % 4 == 0) // check if operand are valid
			{
				if (CheckSign(expression[i]) == false || CheckSign(expression[expression.size() - 1]) != true)
				{
					PrintMesg(ret, T_RED, false);
				}
			}
			else if (isdigit(expression[i]) == false) // check if it's digit
			{
				PrintMesg(ret, T_RED, false);
			}
		}
		else if (expression[i] != ' ') // check spaces
		{
			PrintMesg(ret, T_RED, false);
		}
	}
}

// Print message in std or std error with choice color
void	RPN::PrintMesg(std::string errorMsg, std::string color, bl8 flag) const
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
