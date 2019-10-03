/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:39:34 by alagache          #+#    #+#             */
/*   Updated: 2019/06/19 11:23:15 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MAXCHARS 546

# include <stdint.h>

typedef	struct		s_piece
{
	uint64_t		pattern;
	int				x;
	int				y;
	unsigned int	pos[4];
	int				width;
	int				height;
	int				name;
}					t_piece;

int					check_error(const int fd, t_piece *tab);
void				str_to_struct(char *str, t_piece *tab, int cnt);
int					solver(t_piece *tab, int area);
int					printer(int	size, t_piece *tab);
void				correct_pos(t_piece *tab, unsigned int x, unsigned int y);
uint16_t			get_4_bits(char *str);

#endif
