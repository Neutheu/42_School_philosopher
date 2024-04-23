/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:15:38 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/23 13:34:38 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_all(t_main_struct *main_struct, char *message)
{
	free(main_struct->philos);
	printf("%s\n", message);
	return (1);
}
