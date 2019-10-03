/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:42:42 by alagache          #+#    #+#             */
/*   Updated: 2019/05/03 12:07:03 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

uint64_t	can_place(uint16_t *map, t_piece *ptr)
{
	return (*(uint64_t *)(map + ptr->y) & ptr->pattern >> ptr->x);
}

void		put_on_or_off(uint16_t *map, t_piece *ptr)
{
	*(uint64_t *)(map + ptr->y) ^= ptr->pattern >> ptr->x;
}

int			solve(uint16_t *map, t_piece *ptr, int size)
{
	if (ptr->name == 0)
		return (0);
	ptr->y = 0;
	while (size - ptr->height - ptr->y >= 0)
	{
		ptr->x = 0;
		while (size - ptr->width - ptr->x >= 0)
		{
			if (can_place(map, ptr) == 0)
			{
				put_on_or_off(map, ptr);
				if (solve(map, ptr + 1, size) == 0)
					return (0);
				put_on_or_off(map, ptr);
			}
			ptr->x++;
		}
		ptr->y++;
	}
	return (1);
}

int			solver(t_piece *tab, int area)
{
	int			size;
	uint16_t	map[16];

	size = 2;
	ft_bzero(map, sizeof(uint16_t) * 16);
	while (size * size < area)
		size++;
	while (solve(&(*map), tab, size) == 1 && size < 17)
	{
		ft_bzero(map, sizeof(uint16_t) * 16);
		size++;
	}
	if (size == 17 || printer(size, tab) == -1)
		return (-1);
	return (0);
}
