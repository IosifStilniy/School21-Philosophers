#include "phelasafe.h"

static void	rec(int n, int fd)
{
	char	c;

	if (n / 10)
		rec(n / 10, fd);
	c = -1 * (n < 0) * (n % 10) + (n % 10) * (n >= 0) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	rec(n, fd);
}
