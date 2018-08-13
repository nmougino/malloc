/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:28:15 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/08 20:11:39 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Realloc changes the allocated memory with the new size.
** If there is enough space in the current page, and/or there is no need
** for free and malloc again, then it will simply update the used size param.
*/

static void	*ft_realloc_from_large(void *ptr, size_t s, t_page *page)
{
	void	*ret;

	if (s > page->blksize && (s <= page->size - sizeof(t_page)
		- (sizeof(t_mblkid) * page->blkcount)
		|| (s > SMALL && s < page->blks[0].used)))
	{
		page->blks[0].used = s;
		page->blksize = s;
		return (ptr);
	}
	pthread_mutex_unlock(&mutex_stock);
	if (!(ret = malloc(s)))
	{
		pthread_mutex_lock(&mutex_stock);
		return (NULL);
	}
	pthread_mutex_lock(&mutex_stock);
	ft_memcpy(ret, ptr, page->blksize);
	m_pagedelete(page);
	return (ret);
}

static void	*ft_realloc_from_smti(void *ptr, t_page *page, size_t s, size_t id)
{
	void	*ret;

	ret = ptr;
	if (page->blksize < s)
	{
		pthread_mutex_unlock(&mutex_stock);
		if (!(ret = malloc(s)))
		{
			pthread_mutex_lock(&mutex_stock);
			return (NULL);
		}
		pthread_mutex_lock(&mutex_stock);
		ft_memcpy(ret, ptr, page->blksize);
		pthread_mutex_unlock(&mutex_stock);
		free(ptr);
		pthread_mutex_lock(&mutex_stock);
	}
	else
		page->blks[id].used = s;
	return (ret);
}

void		*realloc(void *ptr, size_t s)
{
	t_page	*target;
	size_t	id;

	ft_printf(">>> realloc(%p, %zu)\n", ptr, s);
	if (!ptr)
		return (malloc(s));
	if (!s)
	{
		free(ptr);
		return (malloc(0));
	}
	if (!(target = m_seekptr(ptr, &id)))
		return (NULL);
	pthread_mutex_lock(&mutex_stock);
	if (target->blksize <= SMALL)
		return (returnmain(ft_realloc_from_smti(ptr, target, s, id)));
	else
		return (returnmain(ft_realloc_from_large(ptr, s, target)));
}
