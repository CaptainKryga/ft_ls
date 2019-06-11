/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:45:33 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/04 14:03:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;
	size_t				count;

	count = 0;
	if (n > 0)
	{
		while ((count < n - 1) && (p1[count] == p2[count]))
			count++;
		return ((unsigned char)p1[count] - (unsigned char)p2[count]);
	}
	return (0);
}
