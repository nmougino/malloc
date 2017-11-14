/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:29:08 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 18:05:03 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// t_page	**get_meta(void)
// {
// 	static t_page	*meta = NULL;
//
// 	return (&meta);
// }

void	*ft_malloc(size_t size)
{
	t_page	**meta;
	// t_page	*target;
	(void)size;

	meta = NULL;
	t_page *page;
	page = m_newpage(TINY, 2);
	ft_printf("hello : sizeof(t_page) = %zu\n", sizeof(t_page));
	ft_printf("hello : sizeof(t_mblkid) = %zu\n", sizeof(t_mblkid));
	ft_printf("page->size : %zu\n", page->size);
	ft_printf("page->blkcount : %zu\n", page->blkcount);
	ft_printf("page->blksize : %zu\n", page->blksize);
 // 	meta = get_meta();
	// if (!(target = seek_page(meta, size)))
	// 	m_pageadd(meta, (target = new_page(size > M ? 1 : BPP)))
	return (NULL);
}

int		main(void)
{
	ft_malloc(20);
	return (0);
}
