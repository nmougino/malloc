/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 22:58:12 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/15 18:28:11 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	ft_printf(">>> calloc(%zu, %zu)\n", count, size);
	ptr = malloc(size * count);
	pthread_mutex_lock(&mutex_stock);
	if (ptr)
		ft_bzero(ptr, size * count);
	return (returnmain(ptr));
}
