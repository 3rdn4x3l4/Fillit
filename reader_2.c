/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:42:27 by alagache          #+#    #+#             */
/*   Updated: 2019/06/19 11:22:04 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		correct_pos(t_piece *tab, unsigned	int x, unsigned	int y)
{
	int	i;

	while (y-- > 0)
	{
		i = 0;
		while (i < 4)
		{
			tab->pos[i] -= 4;
			i += 1;
		}
	}
	while (x-- > 0)
	{
		i = 0;
		while (i < 4)
		{
			tab->pos[i] -= 1;
			i += 1;
		}
	}
}

uint16_t	get_4_bits(char *str)
{
	uint16_t	bit;
	int			i;

	i = 3;
	bit = 0;
	while (i >= 0)
	{
		if (str[i] == '#')
			bit ^= (8 >> i);
		i--;
	}
	return (bit);
}
