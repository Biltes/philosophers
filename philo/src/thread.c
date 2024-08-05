/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:46:27 by biltes            #+#    #+#             */
/*   Updated: 2024/08/05 12:21:23 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

void	*pthread(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	if (phil->id % 2)
		usleep(2000);
	while (!ft_check_died(phil))
	{
		if (phil->info->done_eat)
		{
			print_status(phil, phil->id, FINISH);
			break ;
		}
		philo_eat(phil);
		print_status(phil, phil->id, SLEEP);
		philo_pause(phil, phil->info->time_to_sleep);
		print_status(phil, phil->id, THINK);
	}
	return (NULL);
}

void	philo_pause(t_philo *philo, int time_pause)
{
	long long	time;

	time = get_time();
	while (!ft_check_died(philo))
	{
		if (get_time() - time >= time_pause)
			break ;
		usleep(500);
	}
}

int	start(t_philo *phil)
{
	int	i;

	i = 0;
	phil->info->start_time = get_time();
	while (i < phil->info->nb_philo)
	{
		if (pthread_create(&(phil[i].philo_t), NULL,
				pthread, &(phil[i])))
			return (1);
		++i;
	}
	check_meals_and_die(phil);
	i = 0;
	while (i < phil->info->nb_philo)
		pthread_join(phil[i++].philo_t, NULL);
	i = 0;
	while (i < phil->info->nb_philo)
		pthread_mutex_destroy(&(phil->info->fork[i++]));
	pthread_mutex_destroy(&(phil->info->printig));
	pthread_mutex_destroy(&(phil->info->eating));
	pthread_mutex_destroy(&(phil->info->die));
	pthread_mutex_destroy(&(phil->info->nb_meals));
	return (0);
}
