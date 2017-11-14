/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pageseek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:08:50 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 22:21:44 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** This function qill search threw the memory page a page with a corresponding
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
	tmp = *get_meta();
	while (tmp)
	{
		if (tmp->blksize == s)
		{
			i = 0;
			mtab = tmp->blks;
			while (i < tmp->blkcount)
			{
				if (!(mtab[i].used))
					return (tmp);
				++i;
			}
		}
		tmp = tmp->next;
	}
	return (m_pageadd(m_pagenew(s, 100)));
}

void	*m_seekassign(t_page *page, size_t s)
{
	t_mblkid	*blks;
	size_t		i;

	blks = page->blks;
	i = 0;
	while (i < page->blkcount)
	{
		if (!blks[i].used)
		{
			blks[i].used = s;
			return (blks[i].ptr);
		}
		++i;
	}
	return (NULL);
}
