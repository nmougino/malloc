/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pageseek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:08:50 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/08 20:26:22 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** This function will search threw the memory book a page with a corresponding
** blocksize and free space, then return it.
** ATTENTION must not be used with a LARGE parameter
*/

t_page	*m_memseek(size_t s)
{
	t_page		*tmp;
	size_t		i;
	t_mblkid	*mtab;

	if (s > SMALL)
		return (NULL);
	tmp = *get_book();
	while (tmp)
	{
		if (tmp->blksize == s)
		{
			i = 0;
			mtab = tmp->blks;
			while (i < tmp->blkcount)
			{
				if (mtab[i].used == (size_t)-1)
					return (tmp);
				++i;
			}
		}
		tmp = tmp->next;
	}
	return (m_pageadd(m_pagenew(s, 100)));
}

/*
** This function will search threw a memory page and return the first free
** memory plage and return it.
*/

void	*m_seekassign(t_page *page, size_t s)
{
	t_mblkid	*blks;
	size_t		i;

	blks = page->blks;
	i = 0;
	ft_printf(">> SEEK AND ASSIGN TRIGGERED (%zu)\n", s);
	while (i < page->blkcount)
	{
		if (blks[i].used == (size_t)(-1))
		{
			ft_printf(">> SA: available space found (%zu): %zu - %p\n", page->blksize, i, blks[i].ptr);
			blks[i].used = s;
			ft_printf(">> SA: cleaning...\n");
			ft_bzero(blks[i].ptr, page->blksize);
			ft_printf(">> SA: space cleaned...\n");
			return (blks[i].ptr);
		}
		++i;
	}
	ft_printf(">> SA: no available space found: NULL\n");
	return (NULL);
}

/*
** This function will search threw the memory book and return the location of
** the targeted memory.
** If the pointer is not found, then it return NULL, otherwise it return the
** targeted page and assigned *index* to the index of the seeked memory.
*/

t_page	*m_seekptr(void *ptr, size_t *id)
{
	t_page		*page;
	t_mblkid	*mtab;
	size_t		i;

	page = *get_book();
	while (page)
	{
		i = page->blkcount;
		mtab = page->blks;
		while (i--)
		{
			if (mtab[i].ptr == ptr)
			{
				*id = i;
				return (page);
			}
		}
		page = page->next;
	}
	return (NULL);
}
