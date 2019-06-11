/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_output_part_two.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbashiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:50:45 by jbashiri          #+#    #+#             */
/*   Updated: 2019/03/27 17:03:17 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_format			get_t_format(const char *path, char **list,
		struct stat *temp, unsigned int num)
{
	t_format	ret;
	u_int		i;

	ret.len_nlink = 0;
	ret.len_size = 0;
	ret.len_user = 0;
	ret.len_group = 0;
	ret.total_size = 0;
	i = 0;
	while (i < num)
	{
		temp[i] = get_stat(path, *(list + i));
		ret.total_size += temp[i].st_blocks;
		if (len_digital(temp[i].st_nlink) > ret.len_nlink)
			ret.len_nlink = len_digital(temp[i].st_nlink);
		if (len_digital(temp[i].st_size) > ret.len_size)
			ret.len_size = len_digital(temp[i].st_size);
		if (CH_NULL_STR(getpwuid(temp[i].st_uid), pw_name) > ret.len_user)
			ret.len_user = ft_strlen(getpwuid(temp[i].st_uid)->pw_name);
		if (CH_NULL_STR(getgrgid(temp[i].st_gid), gr_name) > ret.len_group)
			ret.len_group = ft_strlen(getgrgid(temp[i].st_gid)->gr_name);
		i++;
	}
	return (ret);
}

void				print_link(const char *path, const char *name)
{
	char		*temp;
	char		*str;
	char		buffer[255];

	ft_memset(buffer, 0, 255);
	temp = ft_strjoin(path, "/");
	str = ft_strjoin(temp, name);
	if (!(g_flags & FLAG_L) && readlink(str, buffer, sizeof(buffer)) != -1)
		ft_printf(" -> %s", buffer);
	ft_strdel(&str);
	ft_strdel(&temp);
}

void				print_long_output_part_two(struct stat	temp,
						t_format format, char *buffer)
{
	ft_printf("%*llu ", format.len_nlink, temp.st_nlink);
	if (!(g_flags & FLAG_MG))
	{
		if (getpwuid(temp.st_uid))
			ft_printf("%*s  ", -format.len_user,
					getpwuid(temp.st_uid)->pw_name);
		else
			ft_printf("%*s  ", -format.len_user, "\0");
	}
	if (getgrgid(temp.st_gid))
		ft_printf("%*s  ", -format.len_group, getgrgid(temp.st_gid)->gr_name);
	else
		ft_printf("%*s  ", -format.len_group, "\0");
	ft_printf("%*lli ", format.len_size, temp.st_size);
	if (g_flags & FLAG_MU)
		get_time(temp.st_atimespec.tv_sec, buffer);
	else if (g_flags & FLAG_U)
		get_time(temp.st_birthtimespec.tv_sec, buffer);
	else
		get_time(temp.st_mtimespec.tv_sec, buffer);
	ft_printf("%s ", buffer);
}

void				print_long_output_buffer(char *buffer, struct stat temp)
{
	get_attr(temp.st_mode, buffer);
	ft_printf("%s", buffer);
}

int					print_long_output(const char *path, char **list, unsigned
int num, char **color_files)
{
	struct stat	temp[num];
	u_int		i;
	char		buffer[255];
	t_format	format;

	format = get_t_format(path, list, temp, num);
	i = 0;
	if (num != 0 && !(g_flags & FLAG_MD))
		ft_printf("total %u\n", format.total_size);
	while (i < num)
	{
		print_long_output_buffer(buffer, temp[i]);
		ft_printf("%c ", get_x_attr(path, *(list + i)));
		print_long_output_part_two(temp[i], format, buffer);
		if (g_flags & FLAG_G)
			ft_printf("%s%s%s", color_files[i], list[i], DEFAULT);
		else
			ft_printf("%s", list[i]);
		ft_memset(buffer, 0, 255);
		print_link(path, *(list + i));
		ft_printf("\n");
		i++;
	}
	return (i);
}
