/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:28:15 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/15 00:52:52 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*ft_realloc_from_large(void *ptr, size_t s, t_page *page)
{
	void	*ret;

	if (s > page->blksize && (s <= page->size - sizeof(t_page)
		- (sizeof(t_mblkid) * page->blkcount)
		|| (s > SMALL && s < page->blks[0].used)))
	{
		page->blks[0].used = s;
		return (ptr);
	}
	if (!(ret = ft_malloc(s)))
		return (NULL);
	ft_memcpy(ret, ptr, s);
	m_pagedelete(page);
	return (ret);
}

static void	*ft_realloc_from_smti(void *ptr, t_page *page, size_t s, size_t id)
{
	void	*ret;

	ret = ptr;
	if (page->blksize < s)
	{
		if (!(ret = ft_malloc(s)))
			return (NULL);
		ft_memcpy(ret, ptr, s);
		ft_free(ptr);
	}
	else
		page->blks[id].used = s;
	return (ret);
}

void		*ft_realloc(void *ptr, size_t s)
{
	t_page	*target;
	size_t	id;

	if (!(target = m_seekptr(ptr, &id)))
	{
		ft_dprintf(2, "malloc (nmougino):\n*** error for object %p", ptr);
		ft_putendl_fd(": pointer being realloc'd was not allocated ***", 2);
		exit(-1);
	}
	if (target->blksize <= SMALL)
		return (ft_realloc_from_smti(ptr, target, s, id));
	else
		return (ft_realloc_from_large(ptr, s, target));
}
