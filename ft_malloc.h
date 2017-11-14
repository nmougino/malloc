/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:25:35 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/15 00:01:16 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include "libft.h"

# include <stdio.h> // a supprimer

# define TINY 128 // taille maximum d'une alloc tiny
# define SMALL 1024 // taille maximum d'une alloc small

# define MMAP(X) mmap(0, X, PROT_READ |PROT_WRITE, MAP_ANON |MAP_PRIVATE, -1, 0)

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

// a supprimer

# define DEF		"\033[0m"
# define GRA		"\033[1m"
# define SOU		"\033[4m"
# define BLI		"\033[5m"
# define BLA		"\033[30m"
# define RED		"\033[31m"
# define GRE		"\033[32m"
# define YEL		"\033[33m"
# define BLU		"\033[34m"
# define PUR		"\033[35m"
# define CYA		"\033[36m"
# define WHI		"\033[37m"

void				*ft_malloc(size_t size);
void				ft_free(void *ptr);
void				show_alloc_mem(void);

t_page				**get_book(void);

t_page				*m_memseek(size_t s);
void				*m_seekassign(t_page *page, size_t s);
t_page				*m_seekptr(void *ptr, size_t *id);

t_page				*m_pagenew(size_t size, size_t amount);
void				m_pagedelete(t_page *page);
t_page				*m_pageadd(t_page *new);

void				m_pagedescribe(t_page *page); // sup
#endif
