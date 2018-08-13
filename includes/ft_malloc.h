/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:25:35 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/08 20:13:33 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <pthread.h>
# include "libft.h"
# include <sys/resource.h>

# define TINY 128
# define SMALL 1024

# define PR PROT_READ
# define PW PROT_WRITE
# define MA MAP_ANON
# define MP MAP_PRIVATE

extern pthread_mutex_t mutex_stock;

typedef struct		s_mblkid
{
	size_t			used;
	void			*ptr;
}					t_mblkid;

typedef struct		s_page
{
	struct s_page	*prev;
	struct s_page	*next;
	size_t			size;
	size_t			blkcount;
	size_t			blksize;
	t_mblkid		*blks;
	void			*raw;
}					t_page;

void				show_alloc_mem(void);

t_page				**get_book(void);
void				*returnmain(void *p);

t_page				*m_memseek(size_t s);
void				*m_seekassign(t_page *page, size_t s);
t_page				*m_seekptr(void *ptr, size_t *id);

t_page				*m_pagenew(size_t size, size_t amount);
void				m_pagedelete(t_page *page);
t_page				*m_pageadd(t_page *new);

#endif
