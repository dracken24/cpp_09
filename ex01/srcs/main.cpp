/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:54:04 by nadesjar          #+#    #+#             */
/*   Updated: 2023/04/30 13:32:48 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int main(int32 argc, char **argv)
{
	RPN	calculator;

	if (argc != 2)
	{
		std::string ret = "Error, bad input, need 2 argv <./RPN> <Equation>\n";
		ret += "Valid Equation format ex.: (4 7 + 8 * 2 - 3 /)";
		calculator.PrintMesg(ret, T_RED, false);
		return -1;
	}

	std::cout << T_GREEN << "Equation : " << argv[1] << std::endl;
	std::cout << T_GREEN << "Résultat : " << calculator.CalculRpn(argv[1]) << T_RESET << std::endl;

	return 0;
}
