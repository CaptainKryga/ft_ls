/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:09:05 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 17:33:08 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		get_way_file(const char *path, const char *name, char **ret)
{
	char *temp;

	temp = NULL;
	ft_strdel(ret);
	if (name[0] != '/')
	{
		temp = ft_strjoin(path, "/");
		*ret = ft_strjoin(temp, name);
	}
	else
		*ret = ft_strdup(name);
	ft_strdel(&temp);
}

static void		get_maxlen(const char *path, unsigned int *max_len,
		unsigned int *i)
{
	DIR				*dir;
	char			*str;
	struct dirent	*entry;
	char			buffer[255];

	PR_DIR_INIT;
	while ((entry = readdir(dir)) != NULL)
	{
		if (analise_entry(entry->d_name))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			if ((g_flags & FLAG_L) && (readlink(entry->d_name, buffer,
					sizeof(buffer)) != -1))
			{
				get_way_file(path, buffer, &str);
				IF_GWF;
			}
			(entry->d_namlen > (*max_len)) ? (*max_len = entry->d_namlen) : (0);
			*i += 1;
		}
	}
	closedir(dir);
	if (!(g_flags & FLAG_G) && (*max_len) > 1)
		*max_len += (8 - (*max_len % 8));
	ft_strdel(&str);
}

static void		put_list(const char *path, char **list_files,
		char **color_files, unsigned int *i)
{
	DIR				*dir;
	char			*str;
	struct dirent	*entry;
	char			buffer[255];

	PR_DIR_INIT;
	while ((entry = readdir(dir)) != NULL)
	{
		if (analise_entry(entry->d_name))
		{
			ft_memset(buffer, 0, sizeof(buffer));
			get_way_file(path, entry->d_name, &str);
			if ((g_flags & FLAG_L) && (readlink(str, buffer,
					sizeof(buffer)) != -1))
			{
				get_way_file(path, buffer, &str);
				IF_GWF;
			}
			get_way_file(path, entry->d_name, &str);
			(color_files)[*i] = respec_color_part_two(str);
			(list_files)[(*i)++] = ft_strdup(entry->d_name);
		}
	}
	ft_strdel(&str);
	closedir(dir);
}

void			free_mas(char **str, int x)
{
	int i;

	i = 0;
	while (x > i)
		free(str[i++]);
	free(str);
}

unsigned int	print_dir(const char *path, u_int flags)
{
	unsigned int	max_len;
	unsigned int	i;
	char			**list_files;
	char			**color_files;

	INC;
	list_files = (char**)malloc(sizeof(char*) * i);
	color_files = (char**)malloc(sizeof(char*) * i);
	put_list(path, list_files, color_files, &i);
	color_sort_alpha(&list_files, i, &color_files);
	if (flags & FLAG_MT)
		(flags & FLAG_MU) ? (sort_flag_u(path, &list_files, i, &color_files))
		: (sort(path, &list_files, i, &color_files));
	(flags & FLAG_MR) ? (reverse(&list_files, i, &color_files)) : (0);
	(flags & FLAG_MF) ? (sort_flag_f(&list_files, i, &color_files)) : (0);
	if ((flags & FLAG_ML) && !(flags & FLAG_C))
		print_long_output(path, list_files, i, color_files);
	else
		(flags & FLAG_G) ? (print_output_color(list_files, i, max_len,
				color_files)) : (print_output(list_files, i, max_len));
	free_mas(list_files, i);
	free(color_files);
	return (i);
}
