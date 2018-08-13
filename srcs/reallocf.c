/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:45:25 by nmougino          #+#    #+#             */
/*   Updated: 2018/07/15 18:28:29 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*reallocf(void *ptr, size_t s)
{
	ft_printf(">>> reallocf(%p, %zu)\n", ptr, s);
	return (realloc(ptr, s));
}
