/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:38:08 by biltes            #+#    #+#             */
/*   Updated: 2024/08/05 11:59:00 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

void	death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->die));
	philo->info->died = 1;
	pthread_mutex_unlock(&(philo->info->die));
}

void	done_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->die));
	philo->info->done_eat = 1;
	pthread_mutex_unlock(&(philo->info->die));
}

int	ft_check_died(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->die));
	if (philo->info->died)
	{
		pthread_mutex_unlock(&(philo->info->die));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->die));
	return (0);
}

int	check_death(t_philo *philo)
{
	int			i;
	long long	time;

	pthread_mutex_lock(&philo->info->nb_meals);
	if (philo->info->must_eat > 0 && \
		philo->info->count >= philo->info->nb_philo)
		done_eat(philo);
	pthread_mutex_unlock(&philo->info->nb_meals);
	i = 0;
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_lock(&(philo->info->eating));
		time = philo[i].last_ate;
		pthread_mutex_unlock(&(philo->info->eating));
		if (get_time() - time >= philo->info->time_to_die)
		{
			print_status(philo, i, DIE);
			death(philo);
		}
		if (ft_check_died(philo))
			return (1);
		i++;
	}
	return (0);
}

void	check_meals_and_die(t_philo *philo)
{
	while (!philo->info->done_eat)
	{
		usleep(200);
		if (check_death(philo) || philo->info->done_eat)
			break ;
	}
}
