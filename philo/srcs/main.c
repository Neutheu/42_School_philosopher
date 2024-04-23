/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:20:21 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/23 13:27:03 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_main_struct	main_struct;
	int				return_value;

	if (argc != 5 && argc != 6)
	{
		printf("Bad parameters entered\n");
		return (1);
	}
	return_value = initialisation(&main_struct, argc, argv);
	if (return_value)
		return (return_value);
	return (0);
}
