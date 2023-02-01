/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:02:24 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 13:27:57 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_str_is_number(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] < '0' || string[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_mod(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	unsigned long	i;
	void			*ptr1;

	i = 0;
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		while (i < (count * size))
		{
			ptr[i] = '\0';
			i++;
		}
	}
	ptr1 = (void *)ptr;
	return (ptr1);
}

int	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (ft_error("Error:pthread_mutex_destroy() failed \n"));
		i++;
	}
	if (pthread_mutex_destroy(&data->mut_death) != 0)
		return (ft_error("Error:pthread_mutex_destroy() failed \n"));
	free(data->forks);
	free(data->t);
	free(data->fork_taken);
	return (0);
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}
