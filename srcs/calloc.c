/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 22:58:12 by nmougino          #+#    #+#             */
/*   Updated: 2018/08/13 22:37:49 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	pthread_mutex_lock(&g_mutex_stock);
	if (ptr)
		ft_bzero(ptr, size * count);
	return (returnmain(ptr));
}
