/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_page.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:33:35 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/08 18:36:47 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Memory pages management department
*/

t_page					*m_pageadd(t_page *new)
{
	t_page	**book;

	book = get_book();
	if (*book)
	{
		new->prev = (*book)->prev;
		if ((*book)->prev)
			(*book)->prev->next = new;
		new->next = *book;
		(*book)->prev = new;
	}
	*book = new;
	return (new);
}

void					m_pagedelete(t_page *page)
{
	t_page	**book;

	book = get_book();
	if (*book == page)
		*book = page->next;
	if (page->prev)
		page->prev->next = page->next;
	if (page->next)
		page->next->prev = page->prev;
	ft_bzero(page, page->size);
	munmap(page, page->size);
}

static inline void		m_blkinit(t_mblkid *blks, size_t s, size_t blksize)
{
	size_t	i;
	void	*raw;

	i = 0;
	raw = (void*)((unsigned long)blks + (s * sizeof(t_mblkid)));
	while (i < s)
	{
		blks[i].used = (size_t)(-1);
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
	page->blks = (t_mblkid*)((unsigned long)page + sizeof(t_page));
	page->raw = (void*)((unsigned long)(page->blks)
		+ (amount * sizeof(t_mblkid)));
	m_blkinit(page->blks, amount, size);
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

t_page					*m_pagenew(size_t size, size_t amount)
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
	page = mmap(0, finalsize, PR | PW, MA | MP, -1, 0);
	return (m_pageinit((t_page*)page, size, amount, finalsize));
}
