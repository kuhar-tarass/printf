/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrW.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:55:45 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/02 22:12:02 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "ft_printf.h"

char	*ft_getstrW(wchar_t const *s)
{
	int		i;
	char	*result;
	char	*tmp;

	result = 0;
	i = 0;
	if (s)
		while(s[i])
		{
			tmp = ft_strjoin(result, (char *)ft_getcharW(s[i++]));
			if(result)
				free(result);
			result = tmp;
		}
	return (result);
}
