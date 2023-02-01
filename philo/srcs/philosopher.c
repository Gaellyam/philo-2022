/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:00:24 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 13:27:45 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->t = ft_calloc(1, sizeof(pthread_t) * (data->nbr_philo + 1));
	data->forks = ft_calloc(1, sizeof(pthread_mutex_t) * data->nbr_philo);
	data->fork_taken = ft_calloc(1, sizeof(bool) * data->nbr_philo);
	if (free_when_error(data) == 1)
		return (1);
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error("Error:pthread_mutex_init() failed \n"));
		data->fork_taken[i] = false;
		i++;
	}
	if (pthread_mutex_init(&data->mut_death, NULL) != 0)
		return (ft_error("Error:pthread_mutex_init() failed \n"));
	if (pthread_mutex_lock(&data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_lock() failed \n"));
	data->philo_die = 0;
	if (pthread_mutex_unlock(&data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_unlock() failed \n"));
	return (0);
}

int	check_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_error("Error: Wrong numbers of arguments given\n"));
	while (i < ac)
	{
		if (ft_str_is_number(av[i]))
			return (ft_error("Error: Only digits is recommanded\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	if (check_arguments(ac, av))
		return (1);
	data.nbr_philo = ft_atoi_mod(av[1]);
	data.time_to_die = ft_atoi_mod(av[2]);
	data.time_to_eat = ft_atoi_mod(av[3]);
	data.time_to_sleep = ft_atoi_mod(av[4]);
	if (ac == 6)
		data.total_meal = ft_atoi_mod(av[5]);
	else
		data.total_meal = -1;
	ret = init_mutex(&data);
	if (ret == 0)
	{
		ret = philo_loop(&data);
		ret = ft_destroy_mutex(&data);
	}
	return (ret);
}
