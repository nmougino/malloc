/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:29:08 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/15 02:02:48 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_page	**get_book(void)
{
	static t_page	*book = NULL;

	return (&book);
}

void	*malloc(size_t s)
{
	t_page	*page;

	if (s > SMALL)
	{
		if (!(page = m_pageadd(m_pagenew(s, 1))))
			return (NULL);
	}
	else if (!(page = m_memseek(s <= TINY ? TINY : SMALL)))
		return (NULL);
	if (s > SMALL)
	{
		(page->blks)[0].used = s;
		return (page->blks[0].ptr);
	}
	else
		return (m_seekassign(page, s));
}
