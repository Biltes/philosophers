/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:44:13 by biltes            #+#    #+#             */
/*   Updated: 2024/08/04 17:58:34 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

int	solo_philo(t_philo *philo)
{
	print_status(philo, philo->id, TAKE);
	philo_pause(philo, philo->info->time_to_die);
	print_status(philo, philo->id, DIE);
	return (0);
}

void	take_fork(t_philo *philo, int lfork, int rfork, int id)
{
	pthread_mutex_lock(&(philo->info->nb_meals));
	philo->ate++;
	if (philo->ate == philo->info->must_eat)
		philo->info->count++;
	pthread_mutex_unlock(&(philo->info->nb_meals));
	pthread_mutex_lock(&(philo->info->fork[lfork]));
	philo->info->fork_status[lfork] = 1;
	philo->info->sig[lfork] = philo->id;
	print_status(philo, id, TAKE);
	pthread_mutex_unlock(&(philo->info->fork[lfork]));
	pthread_mutex_lock(&(philo->info->fork[rfork]));
	philo->info->fork_status[rfork] = 1;
	philo->info->sig[rfork] = philo->id;
	print_status(philo, id, TAKE);
	pthread_mutex_unlock(&(philo->info->fork[rfork]));
}

int	check_fork_status(t_philo *philo)
{
	int	rfork;
	int	lfork;
	int	rsig;
	int	lsig;

	if (philo->info->nb_philo == 1)
	{
		solo_philo(philo);
		return (0);
	}
	pthread_mutex_lock(&(philo->info->fork[philo->rfork]));
	rfork = philo->info->fork_status[philo->rfork];
	rsig = philo->info->sig[philo->rfork];
	pthread_mutex_unlock(&(philo->info->fork[philo->rfork]));
	pthread_mutex_lock(&(philo->info->fork[philo->lfork]));
	lfork = philo->info->fork_status[philo->lfork];
	lsig = philo->info->sig[philo->lfork];
	pthread_mutex_unlock(&(philo->info->fork[philo->lfork]));
	if (lfork == 0 && rfork == 0 && lsig != philo->id && rsig != philo->id)
	{
		take_fork(philo, philo->lfork, philo->rfork, philo->id);
		return (1);
	}
	return (0);
}

void	put_down_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->lfork]));
	philo->info->fork_status[philo->lfork] = 0;
	pthread_mutex_unlock(&(philo->info->fork[philo->lfork]));
	pthread_mutex_lock(&(philo->info->fork[philo->rfork]));
	philo->info->fork_status[philo->rfork] = 0;
	pthread_mutex_unlock(&(philo->info->fork[philo->rfork]));
}

void	philo_eat(t_philo *philo)
{
	while (!ft_check_died(philo))
	{
		usleep(100);
		if (check_fork_status(philo))
			break ;
	}
	print_status(philo, philo->id, EAT);
	philo_pause(philo, philo->info->time_to_eat);
	pthread_mutex_lock(&(philo->info->eating));
	philo->last_ate = get_time();
	pthread_mutex_unlock(&(philo->info->eating));
	put_down_fork(philo);
}
