/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:47:07 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 23:38:29 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

char	*get_type(size_t s)
{
	if (s <= TINY)
		return ("TINY");
	if (s <= SMALL)
		return ("SMALL");
	return ("LARGE");
}

void	show_alloc_mem(void)
{
	t_page		*page;
	t_mblkid	*mtab;
	size_t		tot;
	size_t		i;

	page = *get_book();
	tot = 0;
	while (page)
	{
		i = 0;
		mtab = page->blks;
		ft_printf("%s : %p\n", get_type(page->blksize), page);
		while (i < page->blkcount)
		{
			if (mtab[i].used)
				ft_printf("%p - %p : %zu octets\n", mtab[i].ptr,
				(unsigned long)(mtab[i].ptr) + mtab[i].used, mtab[i].used);
			tot += mtab[i].used;
			i++;
		}
		page = page->next;
	}
	ft_printf("Total : %zu octets\n", tot);
}
