/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:01:11 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 13:27:16 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->nbr_philo == 1)
	{
		if (pthread_mutex_lock(&philo->data->forks[0]) != 0)
			return (ft_error("Error:pthread_mutex_lock() failed \n"));
		if (message(philo, "has taken a fork", philo->begin_time, 0) != 0)
			return (1);
		if (usleep(philo->data->time_to_die * 1000) != 0)
			return (ft_error("Error:usleep() failed \n"));
		if (message(philo, "died", philo->begin_time, 1) != 0)
			return (1);
		if (pthread_mutex_unlock(&philo->data->forks[0]) != 0)
			return (ft_error("Error:pthread_mutex_unlock() failed \n"));
		return (1);
	}
	return (0);
}

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (one_philo(philo) != 0)
		return (NULL);
	while (1)
	{
		if (check_dead(philo, philo->begin_time,
				philo->begin_last_meal, philo->cpy_begin_l_m) == 1)
			break ;
		if (take_forks(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		if (message(philo, "is sleeping",
				philo->begin_time, 0) != 0)
			break ;
		ft_sleep(philo, 2);
		if (message(philo, "is thinking",
				philo->begin_time, 0) != 0)
			break ;
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->t[i], NULL))
			return (ft_error("Error:pthread_join() failed \n"));
		i++;
	}
	return (0);
}

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->nbr_philo)
	{
		if ((i + 1) % 2 == 0)
			usleep(500);
		ret = pthread_create(&data->t[i], NULL, philo_thread, &philo[i]);
		if (ret)
			return (ft_error("Error:pthread_create() failed \n"));
		i++;
	}
	return (ret);
}

int	philo_loop(t_data *data)
{
	int				i;
	t_philo			*philo;
	int				ret;

	philo = ft_calloc(1, sizeof(philo) * (data->nbr_philo));
	if (!philo)
		return (ft_error("Error: calloc () failed \n"));
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].begin_last_meal = 0;
		philo[i].cpy_begin_l_m = 0;
		philo[i].begin_time = get_time();
		philo[i].times_eaten = 0;
		philo[i].cpy_begin_l_m = philo[i].begin_time;
		i++;
	}
	ret = create_threads(data, philo);
	ret = join_threads(data);
	free(philo);
	return (ret);
}
