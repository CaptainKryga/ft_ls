/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:35:08 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/11 09:07:51 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_string(const void *arg)
{
	const char **s = (const char **)arg;

	if (*s == NULL)
		return (ft_strdup("(null)"));
	return (ft_strdup(*s));
}
