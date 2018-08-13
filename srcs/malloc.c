/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:29:08 by nmougino          #+#    #+#             */
/*   Updated: 2018/08/13 22:38:35 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t g_mutex_stock = PTHREAD_MUTEX_INITIALIZER;

t_page	**get_book(void)
{
	static t_page	*book = NULL;

	return (&book);
}

void	*returnmain(void *p)
{
	pthread_mutex_unlock(&g_mutex_stock);
	return (p);
}

void	*malloc(size_t s)
{
	t_page			*page;
	struct rlimit	rlp;

	pthread_mutex_lock(&g_mutex_stock);
	getrlimit(RLIMIT_DATA, &rlp);
	if (s > rlp.rlim_cur)
		return (returnmain(NULL));
	if (s > SMALL)
	{
		if (!(page = m_pageadd(m_pagenew(s, 100))))
			return (returnmain(NULL));
	}
	else if (!(page = m_memseek(s <= TINY ? TINY : SMALL)))
		return (returnmain(NULL));
	if (s > SMALL)
	{
		(page->blks)[0].used = s;
		ft_bzero(page->blks[0].ptr, page->blksize);
		return (returnmain(page->blks[0].ptr));
	}
	else
		return (returnmain(m_seekassign(page, s)));
}
