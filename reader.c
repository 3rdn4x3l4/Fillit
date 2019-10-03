/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:42:38 by alagache          #+#    #+#             */
/*   Updated: 2019/06/19 11:22:12 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

void		width_height(t_piece *tab)
{
	unsigned int	x_i;
	unsigned int	y_i;
	unsigned int	coor[4];
	int				i;

	i = 0;
	coor[0] = 3;
	coor[1] = 3;
	coor[2] = 0;
	coor[3] = 0;
	while (i < 4)
	{
		x_i = tab->pos[i] % 4;
		y_i = tab->pos[i] / 4;
		coor[0] = ((coor[0] > x_i) ? x_i : coor[0]);
		coor[1] = ((coor[1] > y_i) ? y_i : coor[1]);
		coor[2] = ((coor[2] < x_i) ? x_i : coor[2]);
		coor[3] = ((coor[3] < y_i) ? y_i : coor[3]);
		i++;
	}
	tab->width = coor[2] - coor[0] + 1;
	tab->height = coor[3] - coor[1] + 1;
	correct_pos(tab, coor[0], coor[1]);
}

void		get_pos(t_piece *tab, const char *pos)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 4)
	{
		if (pos[i] == '#')
		{
			tab->pos[j] = i - i / 5;
			j++;
		}
		i++;
	}
	width_height(tab);
}

uint16_t	raw_16patt(char *pos)
{
	uint16_t	patt_16;
	uint16_t	bits;
	int			i;

	i = 0;
	patt_16 = 0;
	while (i < 4)
	{
		bits = get_4_bits(pos + (i * 5));
		patt_16 += (bits << (4 * i));
		i++;
	}
	return (patt_16);
}

uint64_t	corr_16_to_64(uint16_t patt_16)
{
	uint64_t	patt_64;
	uint16_t	mask16;
	uint64_t	mask64;
	int			i;

	mask16 = 0xF000;
	patt_64 = 0;
	i = 0;
	while (i < 4)
	{
		patt_64 <<= 16;
		patt_64 ^= patt_16 & mask16;
		patt_16 <<= 4;
		i++;
	}
	mask64 = 0x8000800080008000;
	while ((mask64 & patt_64) == 0)
		patt_64 <<= 1;
	mask64 = 0x000000000000F000;
	while ((mask64 & patt_64) == 0)
		patt_64 >>= 16;
	return (patt_64);
}

void		str_to_struct(char *str, t_piece *tab, const int cnt)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	ft_bzero(tab, sizeof(t_piece) * 27);
	while (c < cnt)
	{
		tab->name = c + 'A';
		get_pos(tab, str + i);
		tab->pattern = corr_16_to_64(raw_16patt(str + i));
		c += 1;
		i += 21;
		tab += 1;
	}
}
