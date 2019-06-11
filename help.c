/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbashiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:26:50 by jbashiri          #+#    #+#             */
/*   Updated: 2019/03/25 16:16:09 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*respec_color_part_two(char *str)
{
	struct stat		temp;
	char			*color;
	char			*access;

	COLOUR;
	stat(str, &temp);
	get_attr(temp.st_mode, access);
	if (readlink(str, NULL, 0) != -1 && (!(g_flags & FLAG_L)))
		lstat(str, &temp);
	if (S_ISBLK(temp.st_mode))
		color = FR_WHITE_BG_BLUE;
	if (S_ISCHR(temp.st_mode))
		color = FR_WHITE_BG_BLUE;
	if (S_ISDIR(temp.st_mode))
		respec_color_part_three(access, &color, temp, 1);
	if (S_ISFIFO(temp.st_mode))
		color = FR_RED;
	if (S_ISREG(temp.st_mode))
		respec_color_part_three(access, &color, temp, 2);
	if (S_ISLNK(temp.st_mode))
		color = FR_PURPLE;
	if (S_ISSOCK(temp.st_mode))
		color = FR_YELLOW;
	ft_strdel(&access);
	return (color);
}

void				respec_flags(void)
{
	if (g_flags & FLAG_MF)
	{
		if (!(g_flags & FLAG_MA))
			g_flags |= FLAG_MA;
		if (!(g_flags & FLAG_U))
			g_flags |= FLAG_MU;
		if (g_flags & FLAG_MT)
			g_flags ^= FLAG_MT;
	}
	if (g_flags & FLAG_MD)
		if (!(g_flags & FLAG_MA))
			g_flags |= FLAG_MA;
	if (g_flags & FLAG_MG)
		if (!(g_flags & FLAG_ML))
			g_flags |= FLAG_ML;
}

int					analise_entry(char *name)
{
	size_t			len;

	len = ft_strlen(name);
	if (len == 1)
	{
		if (!(g_flags & FLAG_MA) && name[0] == '.')
			return (0);
		else if (g_flags & FLAG_MD && name[0] == '.')
			return (1);
	}
	if (len == 2 && !(g_flags & FLAG_MD))
		if (!(g_flags & FLAG_MA) && name[0] == '.' && name[1] == '.')
			return (0);
	if (len > 2 && !(g_flags & FLAG_MD))
		if ((!(g_flags & FLAG_A) && !(g_flags & FLAG_MA)) && name[0] == '.')
			return (0);
	if (g_flags & FLAG_MD)
		return (0);
	return (1);
}

void				recursive_print_output(char **list, unsigned int num,
		unsigned int max_len, int flag)
{
	struct winsize	ws;
	unsigned int	col;
	unsigned int	str;
	unsigned int	i;
	unsigned int	j;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	i = 0;
	col = (ws.ws_col) ? (ws.ws_col / (max_len + 1)) : (1);
	str = (num % col) ? (num / col + 1) : (num / col);
	while (i < str)
	{
		j = i;
		while (j < num)
		{
			if (flag == 1)
				ft_printf("%s%*s%s", list[j + 1], -max_len, list[j], DEFAULT);
			else
				ft_printf("%*s", -max_len, list[j]);
			j += str;
		}
		printf("\n");
		i += 2;
	}
}

void				color_sort_alpha(char ***list,
						const u_int size, char ***color_files)
{
	char			*temp_d;
	u_int			i;
	u_int			j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp((*list)[i], (*list)[j]) < 0)
			{
				temp_d = (*list)[i];
				(*list)[i] = (*list)[j];
				(*list)[j] = temp_d;
				temp_d = (*color_files)[i];
				(*color_files)[i] = (*color_files)[j];
				(*color_files)[j] = temp_d;
			}
			j++;
		}
		i++;
	}
}
