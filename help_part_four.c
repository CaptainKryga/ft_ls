/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_part_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbashiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:24:25 by jbashiri          #+#    #+#             */
/*   Updated: 2019/03/27 17:03:17 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_union			*create_union(void)
{
	t_union		*new;

	new = (t_union*)malloc(sizeof(t_union));
	new->len_group = 0;
	new->len_nlink = 0;
	new->len_size = 0;
	new->len_user = 0;
	new->total_size = 0;
	new->i = 0;
	return (new);
}

void			recursive_print_long_output_file_two(t_union *map,
					char **list, unsigned int num)
{
	struct stat	temp;

	while (map->i < num)
	{
		if (lstat(*(list + map->i), &temp))
			perror("ft_ls");
		map->total_size += temp.st_blocks;
		if (len_digital(temp.st_nlink) > map->len_nlink)
			map->len_nlink = len_digital(temp.st_nlink);
		if (len_digital(temp.st_size) > map->len_size)
			map->len_size = len_digital(temp.st_size);
		if (ft_strlen(getpwuid(temp.st_uid)->pw_name) > map->len_user)
			map->len_user = ft_strlen(getpwuid(temp.st_uid)->pw_name);
		if (ft_strlen(getgrgid(temp.st_gid)->gr_name) > map->len_group)
			map->len_group = ft_strlen(getgrgid(temp.st_gid)->gr_name);
		map->i += 2;
	}
}

void			recursive_print_long_output_file_three(char *buffer,
					struct stat temp, char **list, t_union *map)
{
	ft_printf("%s", buffer);
	ft_printf("%c ", get_x_attr_file(*(list + map->i)));
	ft_printf("%*llu ", map->len_nlink, temp.st_nlink);
	ft_printf("%*s  ", -map->len_user, getpwuid(temp.st_uid)->pw_name);
	ft_printf("%*s  ", -map->len_group, getgrgid(temp.st_gid)->gr_name);
	ft_printf("%*llu ", map->len_size, temp.st_size);
	if (g_flags & FLAG_MU)
		get_time(temp.st_atimespec.tv_sec, buffer);
	else if (g_flags & FLAG_U)
		get_time(temp.st_birthtimespec.tv_sec, buffer);
	else
		get_time(temp.st_mtimespec.tv_sec, buffer);
	ft_printf("%s ", buffer);
	if (g_flags & FLAG_G)
	{
		ft_printf("%s", list[map->i + 1]);
		ft_printf("%s", list[map->i]);
		ft_printf("%s", DEFAULT);
	}
	else
		ft_printf("%s", list[map->i]);
}

void			recursive_print_long_output_file(char **list, unsigned int num)
{
	struct stat	temp;
	char		buffer[255];
	t_union		*map;

	map = create_union();
	recursive_print_long_output_file_two(map, list, num);
	map->i = 0;
	while (map->i < num)
	{
		lstat(*(list + map->i), &temp);
		get_attr(temp.st_mode, buffer);
		recursive_print_long_output_file_three(buffer, temp, list, map);
		ft_memset(buffer, 0, 255);
		if (!(g_flags & FLAG_L) && readlink(list[map->i], buffer,
			sizeof(buffer)) != -1)
			ft_printf(" -> %s", buffer);
		ft_printf("\n");
		map->i += 2;
	}
	free(map);
}
