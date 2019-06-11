/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 09:53:42 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/25 09:02:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(char **file, u_int flags, u_int size)
{
	size_t			max_len;
	unsigned int	i;

	max_len = ft_strlen(*file);
	i = 0;
	while (i < size)
	{
		if (max_len < ft_strlen(*(file + i)))
			max_len = ft_strlen(*(file + i));
		i += 2;
	}
	recursive_sort_alpha(&file, i);
	if (flags & FLAG_MT)
		recursive_sort_files(&file, i);
	if (flags & FLAG_MR)
		recursive_reverse(&file, i);
	if (flags & FLAG_MF)
		recursive_sort_flag_f(&file, i);
	if (flags & FLAG_ML && !(flags & FLAG_C))
		recursive_print_long_output_file(file, i);
	else if (flags & FLAG_G)
		recursive_print_output(file, i, max_len, 1);
	else
		recursive_print_output(file, i, max_len, 0);
}
