/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelasafe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:45 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/23 15:14:39 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHELASAFE_H
# define PHELASAFE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# ifndef INVARGS
#  define INVARGS "invalid args, epta: expected at least 4:\
 number_of_philosophers, time_to_die, time_to_eat, time_to_sleep[, \
 number_of_times_each_philosopher_must_eat]\nAll of them - positive int values\
  that means milliseconds of doing some stuff, bliad"
# endif

# ifndef LOGFRK
#  define LOGFRK "has taken a fork"
# endif

# ifndef LOGEAT
#  define LOGEAT "is eating"
# endif

# ifndef LOGSLP
#  define LOGSLP "is sleeping"
# endif

# ifndef LOGTNK
#  define LOGTNK "is thinking"
# endif

# ifndef LOGDTH
#  define LOGDTH "died"
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef int	t_bool;

typedef struct s_meta {
	pthread_mutex_t		*forks;
	pthread_mutex_t		matyugalnik;
	t_bool				appocalipsis;
	int					dvuhsotiye;
	int					numphelas;
	int					ad;
	int					lifetime;
	int					eattime;
	int					sleeptime;
	int					eatcount;
}	t_meta;

typedef struct s_phela {
	pthread_t			phela;
	t_meta				*meta;
	t_bool				kushoet;
	int					id;
	int					lastmeal;
	int					eatcount;
}	t_phela;

int		customerrhndlr(char *prog, char *txt);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
t_bool	logger(struct timeval *tp, t_phela *phela, char *txt);
void	*what_a_wonderful_life(void *arg);

#endif
