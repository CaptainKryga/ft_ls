/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:32:57 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/04 14:03:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(const char *s, int fd, size_t n)
{
	size_t i;

	if (s == NULL)
		return ;
	i = 0;
	while (i < n)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
