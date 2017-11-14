/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_newpage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:33:35 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 18:01:21 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static inline void		m_blkinit(t_mblkid *blks, size_t s, size_t blksize)
{
	size_t	i;
	void	*raw;

	i = 0;
	raw = (void*)((unsigned long)blks + (s * sizeof(t_mblkid)));
	while (i < s)
	{
		blks[i].ptr = (void*)((unsigned long)raw + (i * blksize));
		++i;
	}
}

static inline t_page	*m_pageinit(t_page *page, size_t const size,
	size_t const amount, size_t pagesize)
{
	if (!page)
		return (NULL);
	ft_bzero(page, pagesize);
	page->prev = NULL;
	page->next = NULL;
	page->size = pagesize;
	page->blkcount = amount;
	page->blksize = size;
	m_blkinit(((void *)((unsigned long)page + sizeof(t_page))), amount, size);
	return (page);
}

/*
**	This function will allocate and init a new memory page.
**	* size * refers to the size of one block in the allocation section
**	* amount * is the number of requested blocks
**	********************
**	Page memory map:
**		t_page *prev
**		t_page *next
**		size_t size : actual size of the page
**		size_t blkcount : number of memory blocks in the page
**		size_t blksize : size in octet of each block
**		t_mblxid[blkcount] : blocks data
**		the following memory is raw user memory for blkcount * blksize
*/

t_page					*m_newpage(size_t size, size_t amount)
{
	const size_t	pagesize = (size_t)getpagesize();
	size_t			finalsize;
	size_t			reqsize;
	void			*page;

	if (!amount || !size)
		return (NULL);
	finalsize = pagesize;
	reqsize = (size + sizeof(t_mblkid)) * amount + sizeof(t_page);
	while (finalsize < reqsize)
		finalsize += pagesize;
	if (size <= SMALL)
		amount += (finalsize - reqsize) / (sizeof(t_mblkid) + size);
	page = MMAP(finalsize);
	return (m_pageinit((t_page*)page, size, amount, finalsize));
}
