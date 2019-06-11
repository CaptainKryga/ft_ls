/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 09:38:46 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/27 17:03:17 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_strcmp_simbol(const char *s1, const char *s2)
{
	int count;

	count = 0;
	while ((s1[count] != '\0') && s2[count] != '\0' && s1[count] == s2[count])
		count++;
	if (ft_isalpha(s1[count]) || ft_isalpha(s2[count]))
		return (ft_tolower(s1[count]) - ft_tolower(s2[count]));
	else
		return ((unsigned char)(s1[count]) - (unsigned char)(s2[count]));
}

struct stat		get_stat(const char *path, const char *name)
{
	struct stat	ret;
	char		*temp;
	char		*str;

	temp = ft_strjoin(path, "/");
	str = ft_strjoin(temp, name);
	(g_flags & FLAG_L) ? (stat(str, &ret)) : (lstat(str, &ret));
	ft_strdel(&str);
	ft_strdel(&temp);
	return (ret);
}

int				file_exist(const char *path)
{
	if (access(path, F_OK) != -1)
		return (1);
	else
		return (0);
}

void			swap_stat_s(struct stat *a, struct stat *b)
{
	struct stat temp_s;

	temp_s = *a;
	*a = *b;
	*b = temp_s;
}

void			swap_string(char **a, char **b)
{
	char *temp_d;

	temp_d = *a;
	*a = *b;
	*b = temp_d;
}
