#include "phelasafe.h"

static int	inition(t_phela ***phelas, t_meta **meta, char **argv)
{
	struct timeval	tp;
	int	i;

	(*meta)->numphelas = ft_atoi(*argv++);
	(*meta)->lifetime = ft_atoi(*argv++);
	(*meta)->eattime = ft_atoi(*argv++);
	(*meta)->sleeptime = ft_atoi(*argv++);
	if ((*meta)->numphelas * (*meta)->lifetime * (*meta)->eattime * (*meta)->sleeptime <= 0)
		return (TRUE);
	(*meta)->eatcount = ft_atoi(*argv);
	if (*argv && (*meta)->eatcount <= 0)
		return (TRUE);
	*phelas = malloc(sizeof(**phelas) * (*meta)->numphelas);
	(*meta)->forks = malloc(sizeof(*(*meta)->forks) * (*meta)->numphelas);
	i = -1;
	while (++i < (*meta)->numphelas)
	{
		(*phelas)[i] = malloc(sizeof((*phelas)[i]));
		(*phelas)[i]->id = i + 1;
		(*phelas)[i]->pomer = FALSE;
		(*phelas)[i]->meta = *meta;
		pthread_mutex_init(&(*meta)->forks[i], NULL);
	}
	gettimeofday(&tp, NULL);
	(*meta)->ad = tp.tv_sec;
	return (FALSE);
}

int	main(int argc, char **argv)
{
	struct timeval	tp[2];
	t_meta			meta;
	t_phela			**phelas;
	int				fullphelas;
	int				i;

	if (argc < 5 || argc > 6 || inition(&phelas, &meta, argv + 1))
		customerrhndlr(ft_strrchr(*argv, '/') + 1, INVARGS);
	i = -1;
	while (++i < meta.numphelas)
	{
		pthread_create(phelas[i], NULL, &what_a_wonderful_life, phelas[i]);
		pthread_detach(phelas[i]);
	}
	meta.appocalipsis = FALSE;
	while (1)
	{
		gettimeofday(&tp[0], NULL);
		fullphelas = 0;
		i = -1;
		while (++i < meta.numphelas)
		{
			if (phelas[i]->pomer && ++fullphelas)
				continue;
			if (meta.eatcount && phelas[i]->eatcount >= meta.eatcount)
				fullphelas++;
			gettimeofday(&tp[1], NULL);
			if (!phelas[i]->kushoet)
				phelas[i]->lastmeal += tp[1].tv_sec - tp[0].tv_sec;
			if (phelas[i]->lastmeal >= meta.lifetime && ++phelas[i]->pomer)
				logger(tp[1].tv_sec - meta.ad, i + 1, LOGDTH);
		}
		if (fullphelas == meta.numphelas && ++meta.appocalipsis)
			break ;
	}
}
