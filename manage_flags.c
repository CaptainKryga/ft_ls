/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 12:33:53 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 09:02:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_flag(char sym, u_int *flag)
{
	if (sym == 'l')
		*flag |= FLAG_ML;
	ELSE_IF_SET_FLAG('a', FLAG_MA);
	ELSE_IF_SET_FLAG('r', FLAG_MR);
	ELSE_IF_SET_FLAG('t', FLAG_MT);
	ELSE_IF_SET_FLAG('R', FLAG_R);
	ELSE_IF_SET_FLAG('u', FLAG_MU);
	ELSE_IF_SET_FLAG('A', FLAG_A);
	ELSE_IF_SET_FLAG('C', FLAG_C);
	ELSE_IF_SET_FLAG('L', FLAG_L);
	ELSE_IF_SET_FLAG('G', FLAG_G);
	ELSE_IF_SET_FLAG('f', FLAG_MF);
	ELSE_IF_SET_FLAG('U', FLAG_U);
	ELSE_IF_SET_FLAG('g', FLAG_MG);
	ELSE_IF_SET_FLAG('d', FLAG_MD);
}

int			manage_flags(const char *str, u_int *flag)
{
	u_int i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[++i])
		set_flag(str[i], flag);
	return (1);
}
