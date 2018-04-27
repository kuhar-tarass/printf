/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrW.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:55:45 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/27 21:47:26 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "ft_printf.h"

void	ft_puttrW(wchar_t const *s)
{
	printf("!!!\n");
	int i;

	i = 0;
	if (s)
		while(s[i])
			ft_putcharW(s[i++]);
}

int	main(int ac, char **av)
{
	wchar_t l[4] = {1092,1090,1030,0};  
	printf("@@\n");
	//ft_puttrW(l);
	ft_putcharW(1092);
	return (0);
}