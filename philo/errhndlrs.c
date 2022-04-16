#include "phelasafe.h"

int	customerrhndlr(char *prog, char *txt)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(txt, 2);
	return (1);
}

void	*logger(int tstmp, int numphela, char *txt)
{
	ft_putnbr_fd(tstmp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(numphela, 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(txt, 1);
	return (NULL);
}
