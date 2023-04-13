/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:08 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/13 01:50:05 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philo_bonus.h"

void	dine(t_philo *ph)
{
	sem_wait(ph->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	sem_wait(ph->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	printf("%ld %d is eating\n", get_time() - ph->start_time, ph->id);
	sem_wait(ph->sem2);
	ph->last_meal = get_time();
	sem_post(ph->sem2);
	ft_usleep(ph->t_to_eat);
	sem_wait(ph->sem3);
	ph->m++;
	sem_post(ph->sem3);
	sem_post(ph->right_fork);
	sem_post(ph->left_fork);
}

void	philos_routine(t_philo *ph)
{
	pthread_t	thread;
	pthread_create(&thread, NULL, is_died_or_full, &ph);
	if (ph->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		print_state(*ph, "is thinking");
		dine(ph);
		print_state(*ph, "is sleeping");
		ft_usleep(ph->t_to_sleep);
	}
}

void	init_all(t_philo *ph, t_info *info, t_sem *sem)
{
	ft_init_vars(ph, info);
	ft_init_sem(ph, sem);
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	t_sem			sem;
	t_philo			*philo;
	t_info			info;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		//sem.forks = malloc(sizeof(sem_t) * info.nb_ph);
		philo->pid = malloc(sizeof(pid_t) * info.nb_ph);
		init_all(philo, &info, &sem);
		process_create(philo);
		waitpid(-1, NULL, 0);
		// threads_join(philo, threads);
		// destroy_sem(&info, sem);
		// ft_free(philo, sem, threads);
	}
	return (0);
}
