/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelasafe_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:45 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/22 20:00:56 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHELASAFE_BONUS_H
# define PHELASAFE_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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

typedef struct s_common {
	sem_t	*matyugalnik;
	sem_t	*stamert;
	int		ad;
	int		eattime;
}	t_common;

typedef struct s_meta {
	sem_t		*forks;
	t_common	*common;
	int			sleeptime;
}	t_meta;

typedef struct s_nkvd {
	pthread_t			*officers;
	t_common			*common;
	t_bool				dvuhsotiy;
	int					numphelas;
	int					fulled;
	int					lifetime;
	int					eatcount;
}	t_nkvd;

typedef struct s_phela {
	pid_t				pid;
	int					id;
	pid_t				omnomnom;
	sem_t				*kushoet;
	char				*semname;
	t_nkvd				*nkvd;
}	t_phela;

typedef struct s_log {
	pthread_t	t;
	t_common	*common;
	t_bool		dvuhsotiy;
	int			id;
	char		*txt;
}	t_log;

int		customerrhndlr(char *prog, char *txt);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strrchr(const char *s, int c);
void	logger(t_common *common, int id, char *txt);
t_phela	*phela(t_phela **phelas, t_phela *phela);
sem_t	*semhndlr(char *semname, int def, sem_t *out);
int		timemachine(int sleeptime, struct timeval tpp[2]);
void	watch(t_phela *phelas, t_nkvd *nkvd);

#endif
