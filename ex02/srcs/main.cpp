/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:02:08 by dracken24         #+#    #+#             */
/*   Updated: 2023/04/30 18:42:39 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int32	main(int32 argc, char **argv)
{
	PmergeMe	containers;

	if (argc < 2)
	{
		containers.PrintMesg("Error, need more than 1 args !!", T_RED, false);
	}

	containers.SetContainers(argc, argv);
	containers.PrintContainers();
	containers.SortNumbers();
	containers.PrintContainers();

	uint32 nbr = -1;
	std::cout << "uint: " << nbr << std::endl;

	return 0;
}
