/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_part_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbashiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:08:45 by jbashiri          #+#    #+#             */
/*   Updated: 2019/03/27 17:03:17 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				respec_color_part_three(char *access, char **color,
		struct stat temp, int flag)
{
	if (flag == 1)
	{
		if (ft_strcmp(access, "drwxrwxrwt\0") == 0)
			*color = FR_BLACK_BG_GREEN;
		else if (S_IWOTH & temp.st_mode)
			*color = BG_YELLOW_FR_BLACK;
		else
			*color = FR_BLUE;
	}
	if (flag == 2)
	{
		if (S_IXUSR & temp.st_mode || S_IXGRP & temp.st_mode ||
			S_IXOTH & temp.st_mode)
			*color = FR_RED;
		else
			*color = DEFAULT;
	}
}

u_int				len_digital(long long value)
{
	u_int i;

	if (value == 0)
		return (1);
	i = 0;
	while (value > 0)
	{
		value /= 10;
		i++;
	}
	return (i);
}

char				*ft_temp(const char *path, const char *filename)
{
	char	*str;
	char	*temp;

	str = ft_strjoin(path, "/");
	temp = str;
	str = ft_strjoin(temp, filename);
	free(temp);
	return (str);
}
