/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:42:34 by alagache          #+#    #+#             */
/*   Updated: 2019/06/18 14:27:41 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "fillit.h"
#include "libft.h"

void	map_str(int size, char *map)
{
	int	i;

	i = 0;
	while (i + 1 < size + 1)
	{
		map[i] = '.';
		i++;
	}
	while (i < size * (size + 1))
	{
		map[i] = ((i + 1) % (size + 1) == 0 ? '\n' : '.');
		i++;
	}
}

void	fill_map(char *map, int size, t_piece *t)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = (t->x + t->pos[i] % 4) + (size + 1) * (t->y + t->pos[i] / 4);
		map[j] = t->name;
		i++;
	}
}

void	pce_to_map(char *map, int size, t_piece *tab)
{
	while (tab->name != 0)
	{
		fill_map(map, size, tab);
		tab++;
	}
}

int		printer(int size, t_piece *tab)
{
	char	*map;

	if ((map = ft_strnew(size * (size + 1))) == NULL)
		return (-1);
	map_str(size, map);
	pce_to_map(map, size, tab);
	write(1, map, size * (size + 1));
	ft_strdel(&map);
	return (0);
}
