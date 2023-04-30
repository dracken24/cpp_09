/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:54:04 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/30 01:17:23 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

// int		main(void)
// {
// 	std::cout << "Bananabomb" << std::endl;

// 	return 0;
// }

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

void	PrintStack(std::stack<int32> stack)
{
	std::stack<int32>
}

int32 EvaluateRpn(const std::string &rpn_expression)
{
	std::istringstream iss(rpn_expression);
	std::stack<int32> operand_stack;
	int32 result = 0;
	std::string token;

	while (iss >> token)
	{
		// std::cout << "ISS: " << iss.str() << "Token: " << token << std::endl;
		std::cout << "Stack: " << operand_stack << "Token: " << token << std::endl;
		if (token == "+")
		{
			int32 operand1 = operand_stack.top();
			operand_stack.pop();
			int32 operand2 = operand_stack.top();
			operand_stack.pop();
			result = operand2 + operand1;
			operand_stack.push(result);
		}
		else if (token == "-")
		{
			int32 operand1 = operand_stack.top();
			operand_stack.pop();
			int32 operand2 = operand_stack.top();
			operand_stack.pop();
			result = operand2 - operand1;
			operand_stack.push(result);
		}
		else if (token == "*")
		{
			int32 operand1 = operand_stack.top();
			operand_stack.pop();
			int32 operand2 = operand_stack.top();
			operand_stack.pop();
			result = operand2 * operand1;
			operand_stack.push(result);
		}
		else if (token == "/")
		{
			int32 operand1 = operand_stack.top();
			operand_stack.pop();
			int32 operand2 = operand_stack.top();
			operand_stack.pop();
			result = operand2 / operand1;
			operand_stack.push(result);
		}
		else
		{
			int32 operand = std::stod(token);
			operand_stack.push(operand);
		}
	}

	return operand_stack.top();
}

int main()
{
	std::string rpn_expression = "4 5 * 6 - 7 * 4 +";
	int32 result = EvaluateRpn(rpn_expression);
	std::cout << "Résultat : " << result << std::endl;

	return 0;
}
