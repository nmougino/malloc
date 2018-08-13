/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 23:45:25 by nmougino          #+#    #+#             */
/*   Updated: 2018/08/13 22:33:00 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*reallocf(void *ptr, size_t s)
{
	void *ans;

	if (!(ans = realloc(ptr, s)))
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}
