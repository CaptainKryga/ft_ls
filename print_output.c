/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 09:52:49 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 16:16:09 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char			*null(int num)
{
	int				x;
	char			*str;

	x = 0;
	str = ft_strnew(num);
	while (x < num)
		str[x++] = ' ';
	return (str);
}

void				ft_print_color_str(unsigned int max_len, char **list,
		char **color_files, unsigned int j)
{
	char			*temp;

	temp = null(max_len - ft_strlen(list[j]));
	ft_printf("%s%s%s%s ", color_files[j], list[j], DEFAULT, temp);
	free(temp);
}

void				print_output_color(char **list, unsigned int num,
		unsigned int max_len, char **color_files)
{
	struct winsize	ws;
	unsigned int	col;
	unsigned int	str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = (ws.ws_col) ? (ws.ws_col / (max_len + 1)) : (1);
	str = (num % col) ? (num / col + 1) : (num / col);
	while (i < str)
	{
		j = i;
		while (j < num)
		{
			ft_print_color_str(max_len, list, color_files, j);
			j += str;
		}
		ft_printf("\n");
		i++;
	}
}

void				print_output(char **list, unsigned int num,
		unsigned int max_len)
{
	struct winsize	ws;
	unsigned int	col;
	unsigned int	str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = (ws.ws_col) ? (ws.ws_col / (max_len + 1)) : (1);
	str = (num % col) ? (num / col + 1) : (num / col);
	while (i < str)
	{
		j = i;
		while (j < num)
		{
			ft_printf("%*s", -max_len, list[j]);
			j += str;
		}
		ft_printf("\n");
		i++;
	}
}
