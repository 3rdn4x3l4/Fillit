/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 09:42:21 by alagache          #+#    #+#             */
/*   Updated: 2019/04/25 10:11:10 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_str(const int fd)
{
	char	tmp[MAXCHARS + 1];
	char	*str;
	int		ret;

	ft_bzero(tmp, (size_t)(MAXCHARS + 1));
	ret = read(fd, tmp, MAXCHARS);
	if (ret == -1 || ret == MAXCHARS)
		return (NULL);
	if (!(str = ft_strdup(tmp)))
		return (NULL);
	if ((ft_strlen(str) + 1) % 21 != 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int		check_1tetri(const char *tetri)
{
	int	i;
	int	nl;
	int	part;
	int	not_part;

	i = 0;
	nl = 0;
	part = 0;
	not_part = 0;
	while (i < 20)
	{
		if (tetri[i] == '\n' && (i + 1) % 5 == 0)
			nl += 1;
		if (tetri[i] == '#' && (i + 1) % 5 != 0)
			part += 1;
		if (tetri[i] == '.' && (i + 1) % 5 != 0)
			not_part += 1;
		i += 1;
	}
	if (nl != 4 || part != 4 || not_part != 12)
		return (-1);
	return (0);
}

int		check_1piece(const	char *str)
{
	int	i;
	int	links;

	i = 0;
	links = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (20 >= i + 1 && str[i + 1] == '#')
				links += 1;
			if (20 >= i + 5 && str[i + 5] == '#')
				links += 1;
		}
		i += 1;
	}
	if (links != 3 && links != 4)
		return (-1);
	return (0);
}

int		check_tetris(const char *str, int cnt_piece)
{
	int	j;

	j = 0;
	while (cnt_piece > 0)
	{
		if (check_1tetri(str + j) == -1)
			return (-1);
		if (check_1piece(str + j) == -1)
			return (-1);
		if (str[j + 20] != '\n' && cnt_piece > 1)
			return (-1);
		j += 21;
		cnt_piece -= 1;
	}
	return (0);
}

int		check_error(const int fd, t_piece *tab)
{
	int		cnt;
	char	*str;

	if ((str = get_str(fd)) == NULL)
		return (-1);
	cnt = (ft_strlen(str) + 1) / 21;
	if (check_tetris(str, cnt) == -1)
	{
		free(str);
		return (-1);
	}
	str_to_struct(str, tab, cnt);
	free(str);
	return (cnt);
}
