/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/15 23:40:00 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	is_died_or_full(t_philo *ph, t_info *info)
{
	int	i;
	int	n;

	while (1)
	{
		i = 0;
		n = 0;
		while (i < ph->nb_ph)
		{
			if (is_died(ph, i) == 0)
				return (0);
			pthread_mutex_lock(ph[i].m3);
			if (ph[i].m != 0 && ph[i].m >= ph[i].nb_m && ph[i].nb_m != -1)
				n++;
			pthread_mutex_unlock(ph[i].m3);
			i++;
		}
		if (n == info->nb_ph)
		{
			usleep(200000);
			return (0);
		}
	}
}

void	dine(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	print_state(*ph, "has taken a fork", 1);
	pthread_mutex_lock(ph->left_fork);
	print_state(*ph, "has taken a fork", 1);
	print_state(*ph, "is eating", 1);
	pthread_mutex_lock(ph->m2);
	ph->last_meal = get_time();
	pthread_mutex_unlock(ph->m2);
	ft_usleep(ph->t_to_eat);
	pthread_mutex_lock(ph->m3);
	ph->m++;
	pthread_mutex_unlock(ph->m3);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	*philos_routine(void *void_philo)
{
	t_philo	*ph;

	ph = (t_philo *)void_philo;
	if (ph->id % 2 == 0)
		ft_usleep(1.5);
	while (1)
	{
		print_state(*ph, "is thinking", 1);
		dine(ph);
		print_state(*ph, "is sleeping", 1);
		ft_usleep(ph->t_to_sleep);
	}
}

void	init_all(t_philo *ph, t_info *info, pthread_mutex_t	*forks)
{
	ft_init_vars(ph, info);
	ft_init_mutex(ph, info, forks);
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_info			info;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		forks = malloc(sizeof(pthread_mutex_t) * info.nb_ph);
		init_all(philo, &info, forks);
		threads_create(philo, threads);
		if (!is_died_or_full(philo, &info))
		{
			threads_detach(philo, threads);
			destroy_mutex(philo, &info, forks);
			ft_free(philo, threads, forks);
			return (1);
		}
	}
	return (0);
}
