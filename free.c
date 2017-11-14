/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 23:50:33 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/15 00:14:09 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_free(void *ptr)
{
	t_page	*target;
	size_t	id;

	if (!(target = m_seekptr(ptr, &id)))
	{
		ft_dprintf(2, "malloc (nmougino):\n*** error for object %p", ptr);
		ft_putendl_fd(": pointer being freed was not allocated ***", 2);
		exit(-1);
	}
	if (target->blksize > SMALL)
		m_pagedelete(target);
	else
	{
		ft_bzero(target->blks[id].ptr, target->blks[id].used);
		target->blks[id].used = 0;
	}
}
