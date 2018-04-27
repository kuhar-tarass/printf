/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:48:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/27 21:47:03 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct		l_key
{
	char			typedata;
	int				field;
	int				precision;
	char			sizex2;
	char			size;
	char			space;
	char			zero;
	char			plus;
	char			minus;
	char			hash;
	
	struct l_key	*next;
}					t_key;

char				*ft_itoa_base(unsigned int n, int base);
void				ft_putcharW(wchar_t c);

#endif