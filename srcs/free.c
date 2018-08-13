/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 23:50:33 by nmougino          #+#    #+#             */
/*   Updated: 2018/08/13 22:37:49 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** free will free the allocated memory from the page's block table.
** if the memory is part of a LARGE page ( > SMALL ) then it will destroy the
** entire page via munmap.
*/

void	free(void *ptr)
{
	t_page	*target;
	size_t	id;

	pthread_mutex_lock(&g_mutex_stock);
	if (!ptr || !(target = m_seekptr(ptr, &id)))
	{
		pthread_mutex_unlock(&g_mutex_stock);
		return ;
	}
	if (target->blksize > SMALL)
		m_pagedelete(target);
	else
	{
		ft_bzero(target->blks[id].ptr, target->blks[id].used);
		target->blks[id].used = (size_t)-1;
	}
	pthread_mutex_unlock(&g_mutex_stock);
}
