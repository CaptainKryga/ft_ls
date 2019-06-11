/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:02:45 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 16:16:09 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <time.h>
#include "ft_printf.h"

static const char	g_month[12][4] =
{
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

char				*get_time(time_t sec, char *buffer)
{
	char	*temp;
	u_int	t_temp;
	time_t	copy;

	copy = sec;
	tzset();
	sec -= timezone;
	temp = get_ls_date(&sec);
	ft_strcpy(buffer, (temp[4] == (char)'1') ? (g_month[10 + temp[5] -
			'1']) : (g_month[temp[5] - '1']));
	FORM_T_1;
	if ((time(NULL) - copy) > 15724800)
	{
		FORM_T_2;
	}
	else
		FORM_T_3;
	ft_strdel(&temp);
	buffer[12] = 0;
	return (buffer);
}

char				get_x_attr(const char *path, const char *filename)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		ret;
	char		*str;

	str = ft_temp(path, filename);
	acl = acl_get_link_np(str, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(str, NULL, 0, XATTR_NOFOLLOW);
	free(str);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		ret = '@';
	else if (acl != NULL)
		ret = '+';
	else
		ret = ' ';
	return (ret);
}

char				get_x_attr_file(const char *filename)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;
	char		ret;

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		ret = '@';
	else if (acl != NULL)
		ret = '+';
	else
		ret = ' ';
	return (ret);
}

char				f_type(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('?');
}

void				get_attr(mode_t permission, char *str)
{
	str[0] = f_type(permission);
	str[1] = (char)((permission & S_IRUSR) ? ('r') : ('-'));
	str[2] = (char)((permission & S_IWUSR) ? ('w') : ('-'));
	str[3] = (char)((permission & S_IXUSR) ? ('x') : ('-'));
	str[4] = (char)((permission & S_IRGRP) ? ('r') : ('-'));
	str[5] = (char)((permission & S_IWGRP) ? ('w') : ('-'));
	str[6] = (char)((permission & S_IXGRP) ? ('x') : ('-'));
	str[7] = (char)((permission & S_IROTH) ? ('r') : ('-'));
	str[8] = (char)((permission & S_IWOTH) ? ('w') : ('-'));
	str[9] = (char)((permission & S_IXOTH) ? ('x') : ('-'));
	if (permission & S_ISTXT)
		str[9] = 't';
	str[10] = 0;
}
