/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:46:28 by biltes            #+#    #+#             */
/*   Updated: 2024/08/05 12:00:47 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TAKE "🍽️ \e[0;32m has taken a fork \033[0m"
# define EAT "🍝 \e[0;34m is eating \033[0m"
# define SLEEP "🛌 \e[0;36m is sleeping \033[0m"
# define THINK "🤔 \e[0;33m is thinking \033[0m"
# define DIE "💀 \033[1;31m died \033[0m"
# define FINISH "ate enough!"

typedef struct s_info
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					done_eat;
	int					*fork_status;
	int					*sig;
	int					count;
	int					died;
	long long			start_time;
	pthread_mutex_t		*fork;
	pthread_mutex_t		eating;
	pthread_mutex_t		nb_meals;
	pthread_mutex_t		die;
	pthread_mutex_t		printig;
}				t_info;

typedef struct s_philo
{
	int			ate;
	int			id;
	long long	last_ate;
	int			lfork;
	int			rfork;
	pthread_t	philo_t;
	t_info		*info;
}				t_philo;

int			ft_isdigit(int num);
int			ft_atoi(char *str);
long long	get_time(void);
void		philo_pause(t_philo *philo, int time_pause);
void		print_status(t_philo *philo, int id, char *is_doing);
int			double_check(int ac, char **av);
void		philo_eat(t_philo *philo);
int			start(t_philo *philo);
void		info_init(t_philo *philo, t_info *info, int ac, char **av);
int			ft_check_died(t_philo *philo);
void		check_meals_and_die(t_philo *phil);

#endif