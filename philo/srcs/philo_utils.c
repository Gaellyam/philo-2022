/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:04:10 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 13:27:28 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long int	get_time(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) != 0)
		return (ft_error("Error: gettimeofday() failed \n"));
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

int	free_when_error(t_data *data)
{
	if (!data->t)
	{
		free (data->forks);
		free (data->fork_taken);
		return (ft_error("Error \n"));
	}
	if (!data->forks)
	{
		free (data->t);
		free (data->fork_taken);
		return (ft_error("Error \n"));
	}
	if (!data->fork_taken)
	{
		free (data->t);
		free (data->forks);
		return (ft_error("Error \n"));
	}
	return (0);
}

int	message(t_philo *philo, char *print_string, long int begin_time, int die)
{
	long int	time_now;

	time_now = get_time();
	if (time_now == 1)
		return (1);
	if (pthread_mutex_lock(&philo->data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_lock() failed \n"));
	if (philo->data->philo_die == 0)
		printf("%ld %d %s\n", time_now - begin_time, philo->id, print_string);
	if (die == 1)
		philo->data->philo_die = 1;
	if (pthread_mutex_unlock(&philo->data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_unlock() failed \n"));
	return (0);
}

int	check_dead(t_philo *philo, long int begin_time,
	long int begin_l_m, long int copy_b_l_m)
{
	int				ret;
	const long int	time_now = get_time();

	ret = 0;
	if (pthread_mutex_lock(&philo->data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_lock() failed \n"));
	if (philo->data->philo_die == 1)
		ret = 1;
	if (pthread_mutex_unlock(&philo->data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_unlock() failed \n"));
	if (ret == 1 || time_now == 1)
		return (1);
	if ((begin_l_m - copy_b_l_m > philo->data->time_to_die && begin_l_m != 0
			&& copy_b_l_m != 0) || (time_now - begin_time
			> philo->data->time_to_die && begin_l_m == 0)
		|| (time_now - begin_l_m > philo->data->time_to_die
			&& begin_l_m != 0))
	{
		message(philo, "died", begin_time, 1);
		ret = 1;
	}
	return (ret);
}

int	ft_sleep(t_philo *philo, int eat_or_sleep)
{
	long int	time;
	long int	begin;

	if (eat_or_sleep == 1)
		time = philo->data->time_to_eat;
	else if (eat_or_sleep == 2)
		time = philo->data->time_to_sleep;
	begin = get_time();
	if (begin == 1)
		return (1);
	while (get_time() - begin < time)
	{
		if (check_dead(philo, philo->begin_time,
				philo->begin_last_meal, philo->cpy_begin_l_m) == 1)
			return (1);
		if (usleep(250) != 0)
			return (ft_error("Error:usleep() failed \n"));
	}
	return (0);
}
