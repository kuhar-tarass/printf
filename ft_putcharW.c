/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharW.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:45:26 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/01 19:52:17 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

static unsigned char *ft_u_strsub(unsigned char const *s, unsigned int start, size_t len)
{
	size_t	i;
	unsigned char	*sub;

	i = 0;
	if (!s)
		return (0);
	sub = (unsigned char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

unsigned char	*ft_getcharW(wchar_t c)
{
	unsigned char symb[4];

	ft_bzero(symb,4);
	if(c < 128)
		symb[0] = c;
	else if (c < 2048)
	{
		symb[0] = (c >> 6 & 31) | 192 ;
		symb[1] = (c & 63) | 128 ;
	}
	else if (c < 65536)
	{
		symb[0] = (c >> 12 & 15) | 224;
		symb[1] = (c >> 6 & 63) | 192 ;
		symb[2] = (c & 63) | 128 ;
	}
	else
	{
		symb[0] = (c >> 18 & 7) | 224;
		symb[1] = (c >> 12 & 63) | 224;
		symb[2] = (c >> 6 & 63) | 192 ;
		symb[3] = (c & 63) | 128 ;
	}
	return (ft_u_strsub(symb, 0, ft_strlen((char *)symb)));
	//write(1, symb,ft_strlen((char *)symb));
}

/*int	main(int ac, char **av)
{
	ft_putcharW(atoi(av[1]));
	return (0);
}*/
/*10
	1111 1111 1111 1111 1111 1111 1111 1111
	0000 0000 0000 0000 0000 0111 1111 1111
			>> 6 
	0000 0000 0000 0000 0000 0000 0001 1111
			<< 27
	1111 1000 0000 0000 0000 0000 0000 0000
			>> 27
	0000 0000 0000 0000 0000 0000 0001 1111
	0000 0000 0000 0000 0000 0111 1111 1111
			<< 26
	1111 1100 0000 0000 0000 0000 0000 0000
			>> 26 
	0000 0000 0000 0000 0000 0000 0011 1111
*/