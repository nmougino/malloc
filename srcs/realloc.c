/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:28:15 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/15 17:30:52 by nmougino         ###   ########.fr       */
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
	if (!(ret = malloc(s)))
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
		if (!(ret = malloc(s)))
			return (NULL);
		ft_memcpy(ret, ptr, s);
		ft_free(ptr);
	}
	else
		page->blks[id].used = s;
	return (ret);
}

void		*realloc(void *ptr, size_t s)
{
	t_page	*target;
	size_t	id;

	if (!ptr)
		return (malloc(s));
	if (!(target = m_seekptr(ptr, &id)))
		return (NULL);
	if (target->blksize <= SMALL)
		return (ft_realloc_from_smti(ptr, target, s, id));
	else
		return (ft_realloc_from_large(ptr, s, target));
}
