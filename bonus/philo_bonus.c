/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:08 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/14 16:14:08 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	dine(t_philo *ph)
{
	sem_wait(ph->forks);
	print_state(*ph, "has taken a fork");
	sem_wait(ph->forks);
	print_state(*ph, "has taken a fork");
	print_state(*ph, "is eating");
	sem_wait(ph->sem2);
	ph->last_meal = get_time();
	sem_post(ph->sem2);
	ft_usleep(ph->t_to_eat);
	sem_wait(ph->sem3);
	ph->m++;
	sem_post(ph->sem3);
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void	philos_routine(t_philo *ph)
{
	pthread_t	thread;

	if (ph->id % 2 == 0)
		ft_usleep(1);
	pthread_create(&thread, NULL, is_died_or_full, ph);
	while (1)
	{
		print_state(*ph, "is thinking");
		dine(ph);
		print_state(*ph, "is sleeping");
		ft_usleep(ph->t_to_sleep);
	}
}

void	init_all(t_philo *ph, t_info *info)
{
	ft_init_philo(ph, info);
	ft_init_sem(ph);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_info			info;
	int				i;
	int				status;

	if (ac > 1 && check_args(av))
	{
		ft_init_vars(av, &info);
		philo = malloc(sizeof(t_philo));
		philo->pid = malloc(sizeof(pid_t) * info.nb_ph);
		init_all(philo, &info);
		process_create(philo);
		waitpid(-1, &status, 0);
		i = 0;
		while (i < philo->nb_ph)
		{
			kill(philo->pid[i], SIGSEGV);
			i++;
		}
	}
	return (0);
}
