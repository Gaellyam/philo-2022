/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:03:21 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 12:27:40 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	try_take_fork(t_philo *philo, int i)
{
	while (1)
	{
		if (pthread_mutex_lock(&philo->data->forks[i]) != 0)
			return (ft_error("Error:pthread_mutex_lock() failed \n"));
		if (philo->data->fork_taken[i] == false)
		{
			philo->data->fork_taken[i] = true;
			if (message(philo, "has taken a fork",
					philo->begin_time, 0) != 0)
				return (1);
			if (pthread_mutex_unlock(&philo->data->forks[i]) != 0)
				return (ft_error("Error:pthread_mutex_unlock() failed \n"));
			break ;
		}
		else
		{
			if (pthread_mutex_unlock(&philo->data->forks[i]) != 0)
				return (ft_error("Error:pthread_mutex_unlock() failed \n"));
		}
		if (check_dead(philo, philo->begin_time,
				philo->begin_last_meal, philo->cpy_begin_l_m) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	put_down_fork(t_philo *philo, int i)
{
	if (pthread_mutex_lock(&philo->data->forks[i]) != 0)
		return (ft_error("Error:pthread_mutex_lock() failed \n"));
	philo->data->fork_taken[i] = false;
	if (pthread_mutex_unlock(&philo->data->forks[i]) != 0)
		return (ft_error("Error:pthread_mutex_unlock() failed \n"));
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (try_take_fork(philo, philo->id - 1) == 1)
		return (1);
	if (philo->id == philo->data->nbr_philo)
	{
		if (try_take_fork(philo, 0) == 1)
			return (1);
	}
	else
	{
		if (try_take_fork(philo, philo->id) == 1)
			return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	philo->begin_last_meal = get_time();
	if (philo->begin_last_meal == 1)
		return (1);
	if (message(philo, "is eating", philo->begin_time, 0) != 0)
		return (1);
	ft_sleep(philo, 1);
	philo->cpy_begin_l_m = philo->begin_last_meal;
	if (philo->id == philo->data->nbr_philo)
	{
		if (put_down_fork(philo, 0) == 1)
			return (1);
	}
	else
	{
		if (put_down_fork(philo, philo->id) == 1)
			return (1);
	}
	if (put_down_fork(philo, philo->id - 1) == 1)
		return (1);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->total_meal)
		return (1);
	return (0);
}
