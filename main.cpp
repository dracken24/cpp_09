/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:36:23 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/20 15:17:04 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bitcoin.hpp"
#include <map>
#include <cstdlib>

int	main(int argc, char **argv)
{
	std::map<int, char *> tmp;
	std::pair<int, char *> pair;

	for (int i = 1; i < argc; i++)
	{
		pair.first = std::atoi(argv[i]);
		pair.second = argv[i];
		tmp.insert(pair);
	}

	for (std::map<int, char *>::iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << it->first << " ";

	std::cout << "\nBouyaga!!!!" << std::endl;
	
	return 0;
}
