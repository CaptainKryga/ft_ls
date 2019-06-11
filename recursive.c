/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:10:01 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/27 17:03:17 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			get_way_file(const char *path, const char *name, char **ret)
{
	char			*temp;

	ft_strdel(ret);
	temp = ft_strjoin(path, "/");
	*ret = ft_strjoin(temp, name);
	ft_strdel(&temp);
}

void				print_permission_denied(char *name)
{
	char			*str;

	str = ft_strjoin("ft_ls: ", name + 1);
	perror(str);
	free(str);
}

static u_int		get_number(const char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	u_int			size;
	struct stat		temp;
	char			*str;

	IF_DIRI;
	str = NULL;
	size = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (analise_entry(entry->d_name))
		{
			get_way_file(path, entry->d_name, &str);
			if ((g_flags & FLAG_MA) ? (N_DOTS(entry->d_name)) :
			(entry->d_name[0] != '.'))
			{
				lstat(str, &temp);
				(S_ISDIR(temp.st_mode)) ? (size++) : (0);
			}
		}
	}
	ft_strdel(&str);
	closedir(dir);
	return (size);
}

static void			put_list(const char *path, char **dir_names)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		temp;
	unsigned int	i;
	char			*str;

	IF_DIRV;
	i = 0;
	str = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (analise_entry(entry->d_name))
		{
			get_way_file(path, entry->d_name, &str);
			if ((g_flags & FLAG_MA) ? (N_DOTS(entry->d_name)) :
			(entry->d_name[0] != '.'))
			{
				lstat(str, &temp);
				if (S_ISDIR(temp.st_mode))
					(dir_names)[i++] = ft_strjoin("/", entry->d_name);
			}
		}
	}
	ft_strdel(&str);
	closedir(dir);
}

void				recursive(const char *path, u_int flags, int depth)
{
	unsigned int	i;
	u_int			size;
	char			**dir_names;
	char			*str;

	if ((size = get_number(path)) == 0)
		return ;
	dir_names = (char**)malloc(sizeof(char*) * size);
	put_list(path, dir_names);
	print_dir(path, flags);
	i = 0;
	while (i < size)
	{
		str = ft_strjoin(path, dir_names[i]);
		ft_printf("\n%s:\n", str + ((str[0] == '/') ? (1) : (0)));
		recursive(str, flags, depth + 1);
		ft_strdel(&str);
		i++;
	}
	free_mas(dir_names, size);
}
