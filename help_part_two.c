/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbashiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:55:11 by jbashiri          #+#    #+#             */
/*   Updated: 2019/03/25 09:02:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			recursive_sort_alpha(char ***list, const u_int size)
{
	char		*temp_d;
	u_int		i;
	u_int		j;

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
				temp_d = (*list)[i + 1];
				(*list)[i + 1] = (*list)[j + 1];
				(*list)[j + 1] = temp_d;
			}
			j += 2;
		}
		i += 2;
	}
}

void			recursive_sort_files_swap(char ***list, struct stat *mas,
		u_int i, u_int j)
{
	struct stat	temp_s;
	char		*temp_d;

	temp_s = mas[i];
	temp_d = (*list)[i];
	mas[i] = mas[j];
	(*list)[i] = (*list)[j];
	mas[j] = temp_s;
	(*list)[j] = temp_d;
	temp_d = (*list)[i + 1];
	(*list)[i + 1] = (*list)[j + 1];
	(*list)[j + 1] = temp_d;
}

void			recursive_sort_files_while(char ***list, struct stat *mas,
		u_int i, u_int size)
{
	u_int		j;

	j = 0;
	while (j < size)
	{
		if (g_flags & FLAG_MU)
		{
			if (mas[i].st_atimespec.tv_sec > mas[j].st_atimespec.tv_sec)
				recursive_sort_files_swap(&(*list), mas, i, j);
			if ((mas[i].st_atimespec.tv_sec == mas[j].st_atimespec.tv_sec)
				&& (ft_strcmp((*list)[i], (*list)[j]) < 0))
				recursive_sort_files_swap(&(*list), mas, i, j);
		}
		else
		{
			if (mas[i].st_mtimespec.tv_sec > mas[j].st_mtimespec.tv_sec)
				recursive_sort_files_swap(&(*list), mas, i, j);
			if ((mas[i].st_mtimespec.tv_sec == mas[j].st_mtimespec.tv_sec)
				&& (ft_strcmp((*list)[i], (*list)[j]) < 0))
				recursive_sort_files_swap(&(*list), mas, i, j);
		}
		j += 2;
	}
}

void			recursive_sort_files(char ***list, const u_int size)
{
	struct stat	mas[size];
	u_int		i;

	i = 0;
	while (i < size)
	{
		if (stat(*(*list + i), &mas[i]))
		{
			perror("ft_ls");
			exit(1);
		}
		i += 2;
	}
	i = 0;
	while (i < size)
	{
		recursive_sort_files_while(&(*list), mas, i, size);
		i += 2;
	}
}

void			recursive_reverse(char ***list, const u_int size)
{
	char		*temp_d;
	u_int		i;

	i = 0;
	while (i < size / 2)
	{
		temp_d = (*list)[i];
		(*list)[i] = (*list)[size - 1 - i];
		(*list)[size - 1 - i] = temp_d;
		temp_d = (*list)[i + 1];
		(*list)[i + 1] = (*list)[size - 1 - (i + 1)];
		(*list)[size - 1 - (i + 1)] = temp_d;
		free(temp_d);
		i += 2;
	}
}
