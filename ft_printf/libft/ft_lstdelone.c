/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:34:59 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/04 14:03:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del) (void*, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	(*alst)->content = NULL;
	(*alst)->content_size = 0;
	*alst = NULL;
}
