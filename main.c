/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:36:36 by alagache          #+#    #+#             */
/*   Updated: 2019/06/18 14:29:54 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_piece	tab[27];
	int		fd;
	int		cnt;

	if (ac != 2)
	{
		ft_putendl_fd("usage : ./fillit path/to/file", 1);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || (cnt = check_error(fd, &tab[0])) == -1)
	{
		close(fd);
		ft_putendl("error");
		return (1);
	}
	close(fd);
	if (solver(&tab[0], cnt * 4) == 0)
		return (0);
	ft_putendl("error");
	return (1);
}
