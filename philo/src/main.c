/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:38:00 by biltes            #+#    #+#             */
/*   Updated: 2024/08/05 11:01:43 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

int	check(int ac, char **av)
{
	int			i;
	int			j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_info		info;

	if (ac > 6 || ac < 5)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (check(ac, av) == 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	if (double_check(ac, av) == 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	info_init(&philo, &info, ac, av);
	return (0);
}
