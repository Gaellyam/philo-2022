/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galamy <galamy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:25:15 by galamy            #+#    #+#             */
/*   Updated: 2023/02/01 13:26:40 by galamy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meal;
	pthread_mutex_t	mut_death;
	pthread_t		*t;
	pthread_mutex_t	*forks;
	bool			*fork_taken;
	int				philo_die;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long int		begin_last_meal;
	int				times_eaten;
	long int		cpy_begin_l_m;
	long int		begin_time;
}					t_philo;

int					ft_str_is_number(char *string);
int					ft_atoi_mod(char *str);
void				*ft_calloc(size_t count, size_t size);
int					ft_destroy_mutex(t_data *data);
int					ft_error(char *str);

long int			get_time(void);
int					free_when_error(t_data *data);
int					message(t_philo *philo,
						char *print_string, long int begin_time, int die);
int					check_dead(t_philo *philo, long int begin_time,
						long int begin_l_m, long int copy_b_l_m);
int					ft_sleep(t_philo *philo, int eat_or_sleep);

int					try_take_fork(t_philo *philo, int i);
int					put_down_fork(t_philo *philo, int i);
int					take_forks(t_philo *philo);
int					eating(t_philo *philo);

int					one_philo(t_philo *philo);
void				*philo_thread(void *data);
int					join_threads(t_data *data);
int					create_threads(t_data *data, t_philo *philo);
int					philo_loop(t_data *data);

int					init_mutex(t_data *data);
int					check_arguments(int ac, char **av);
#endif