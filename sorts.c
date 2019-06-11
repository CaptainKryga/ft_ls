/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 09:35:55 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 10:14:46 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			recursive_sort_flag_f(char ***list, const u_int size)
{
	char	*temp_d;
	u_int	i;
	u_int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp_simbol((*list)[i], (*list)[j]) < 0)
			{
				temp_d = (*list)[i];
				(*list)[i] = (*list)[j];
				(*list)[j] = temp_d;
				temp_d = (*list)[i + 1];
				(*list)[i + 1] = (*list)[j + 1];
				(*list)[j + 1] = temp_d;
			}
			j += 2;
		}
		i += 2;
	}
}

void			sort_flag_f(char ***list, const u_int size, char ***color_files)
{
	u_int i;
	u_int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp_simbol((*list)[i], (*list)[j]) < 0)
				SWAP_L_C;
			j++;
		}
		i++;
	}
}

void			sort(const char *path, char ***list, const u_int size,
		char ***color_files)
{
	struct stat	mas[size];
	u_int		i;
	u_int		j;

	i = 0;
	while (i < size)
	{
		mas[i] = get_stat(path, *(*list + i));
		i++;
	}
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (mas[i].st_mtimespec.tv_sec > mas[j].st_mtimespec.tv_sec)
				SWAP_S_L_C;
			if ((mas[i].st_mtimespec.tv_sec == mas[j].st_mtimespec.tv_sec)
					&& (ft_strcmp((*list)[i], (*list)[j]) < 0))
				SWAP_S_L_C;
			j++;
		}
		i++;
	}
}

void			reverse(char ***list, const u_int size, char ***color_files)
{
	char	*temp_d;
	u_int	i;

	i = 0;
	while (i < size / 2)
	{
		temp_d = (*list)[i];
		(*list)[i] = (*list)[size - 1 - i];
		(*list)[size - 1 - i] = temp_d;
		temp_d = (*color_files)[i];
		(*color_files)[i] = (*color_files)[size - 1 - i];
		(*color_files)[size - 1 - i] = temp_d;
		i++;
	}
}

void			sort_flag_u(const char *path, char ***list, const u_int size,
							char ***color_files)
{
	struct stat	mas[size];
	u_int		i;
	u_int		j;

	i = 0;
	while (i < size)
	{
		mas[i] = get_stat(path, *(*list + i));
		i++;
	}
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (mas[i].st_atimespec.tv_sec > mas[j].st_atimespec.tv_sec)
				SWAP_S_L_C;
			if ((mas[i].st_atimespec.tv_sec == mas[j].st_atimespec.tv_sec)
					&& (ft_strcmp((*list)[i], (*list)[j]) < 0))
				SWAP_S_L_C;
			j++;
		}
		i++;
	}
}
