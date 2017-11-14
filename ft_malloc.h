/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:25:35 by nmougino          #+#    #+#             */
/*   Updated: 2017/11/14 18:01:20 by nmougino         ###   ########.fr       */
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

typedef struct		s_page
{
	struct s_page	*prev;
	struct s_page	*next;
	size_t			size;
	size_t			blkcount;
	size_t			blksize;
}					t_page;

typedef struct		s_mblkid
{
	size_t			used;
	void			*ptr;
}					t_mblkid;

void				*ft_malloc(size_t size);

t_page				*m_newpage(size_t size, size_t amount);

#endif
