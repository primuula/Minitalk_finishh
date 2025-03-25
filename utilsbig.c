/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsbig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:10:48 by safamran          #+#    #+#             */
/*   Updated: 2025/03/25 17:11:13 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*new;

	new = malloc(size * nmemb);
	if (!new)
		return (NULL);
	ft_memset(new, 0, (nmemb * size));
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (((void *)dest == 0) && ((void *)src == 0))
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*d;

	d = (unsigned char *)b;
	while (len > 0)
	{
		*d = (unsigned char)c;
		d++;
		len--;
	}
	return (b);
}
