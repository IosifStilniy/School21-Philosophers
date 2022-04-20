/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelasafe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:48 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/20 19:43:06 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe.h"

static int	checknum(char *str)
{
	int	num;
	int	digcount;

	num = ft_atoi(str);
	digcount = 1;
	while (num / 10 && digcount++)
		num /= 10;
	if ((int)ft_strlen(str) != digcount)
		return (0);
	return (ft_atoi(str));
}

static int	inition(t_phela **phelas, t_meta *meta, char **argv)
{
	int	i;

	meta->numphelas = checknum(*argv++);
	meta->lifetime = checknum(*argv++);
	meta->eattime = checknum(*argv++);
	meta->sleeptime = checknum(*argv++);
	meta->eatcount = checknum(*argv);
	if ((*argv && meta->eatcount <= 0) || meta->numphelas <= 0
		|| meta->lifetime <= 0 || meta->eattime <= 0 || meta->sleeptime <= 0)
		return (TRUE);
	*phelas = malloc(sizeof(**phelas) * meta->numphelas);
	meta->forks = malloc(sizeof(*meta->forks) * meta->numphelas);
	i = -1;
	while (++i < meta->numphelas)
	{
		(*phelas)[i].id = i + 1;
		(*phelas)[i].kushoet = FALSE;
		(*phelas)[i].meta = meta;
		pthread_mutex_init(&meta->forks[i], NULL);
	}
	meta->ad = 0;
	meta->appocalipsis = FALSE;
	pthread_mutex_init(&meta->matyugalnik, NULL);
	return (FALSE);
}

t_bool	morg(t_phela *phelas, t_meta *meta, struct timeval tp[2])
{
	int				fullphelas;
	int				i;

	gettimeofday(&tp[0], NULL);
	tp[1] = tp[0];
	fullphelas = 0;
	i = -1;
	while (++i < meta->numphelas)
	{
		if (meta->eatcount && phelas[i].eatcount >= meta->eatcount)
			fullphelas++;
		while (!((tp[1].tv_sec - tp[0].tv_sec) * 1000 + tp[1].tv_usec / 1000
				- tp[0].tv_usec / 1000))
		{
			usleep(100);
			gettimeofday(&tp[1], NULL);
		}
		if (!phelas[i].kushoet)
			phelas[i].lastmeal += (tp[1].tv_sec - tp[0].tv_sec) * 1000
				+ (tp[1].tv_usec - tp[0].tv_usec) / 1000;
		if (phelas[i].lastmeal >= meta->lifetime && ++meta->appocalipsis)
			return (logger(&tp[1], &phelas[i], LOGDTH));
	}
	return (fullphelas >= phelas->meta->numphelas);
}

int	main(int argc, char **argv)
{
	struct timeval	tp[2];
	t_meta			meta;
	t_phela			*phelas;
	int				i;

	if (argc < 5 || argc > 6 || inition(&phelas, &meta, argv + 1))
		return (customerrhndlr(ft_strrchr(*argv, '/') + 1, INVARGS));
	i = -1;
	while (++i < meta.numphelas)
	{
		pthread_create(&phelas[i].phela, NULL, &what_a_wonderful_life,
			&phelas[i]);
		pthread_detach(phelas[i].phela);
	}
	gettimeofday(&tp[0], NULL);
	meta.ad = tp[0].tv_sec * 1000 + tp[0].tv_usec / 1000;
	while (!meta.appocalipsis)
		meta.appocalipsis = morg(phelas, &meta, tp);
	i = -1;
	while (++i < meta.numphelas)
		pthread_mutex_destroy(&meta.forks[i]);
	pthread_mutex_destroy(&meta.matyugalnik);
	free(meta.forks);
	free(phelas);
	return (0);
}
