/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:29:08 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 22:18:33 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	m_pagedescribe(t_page *page)
{
	ft_putstr("page : ");
	ft_putstr(GRA);
	ft_printf("%p", page);
	ft_putendl(DEF);
	ft_printf("page->size : %zu (%zu page(s))\n", page->size, page->size / getpagesize());
	ft_printf("page->blkcount : %zu\n", page->blkcount);
	ft_printf("page->blksize : %zu\n", page->blksize);
	ft_printf("page->blks : %p\n", page->blks);
	ft_printf("page->raw : %p\n", page->raw);
	ft_printf("page->end : %p\n", page->raw + (page->blkcount * page->blksize));
	ft_printf("\nend - raw : %zu\n", (page->blkcount * page->blksize));
	ft_printf("blks - page = %zu >< sizeof(t_page) = %zu\n", (unsigned long)page->blks - (unsigned long)page, sizeof(t_page));
}

t_page	**get_meta(void)
{
	static t_page	*meta = NULL;

	return (&meta);
}

void	*ft_malloc(size_t s)
{
	t_page	*page;

	if (s > SMALL && !(page = m_pageadd(m_pagenew(s, 1))))
		return (NULL);
	else if (!(page = m_memseek(s < SMALL ? TINY : SMALL)))
		return (NULL);
	if (s > SMALL)
	{
		page->blks[0].used = s;
		return (page->blks[0].ptr);
	}
	else
	{
		m_pagedescribe(page);
		return (m_seekassign(page, s));
	}
}

int		main(void)
{
	char	*str = ft_malloc(6);

	ft_putstr(GRA);
	ft_putstr(CYA);
	ft_printf(" >> %p\n");
	ft_putstr(DEF);
	str[0] = 's';
	str[1] = 'a';
	str[2] = 'l';
	str[3] = 'u';
	str[4] = 't';
	str[5] = '\0';
	ft_putendl(str);
	return (0);
}
