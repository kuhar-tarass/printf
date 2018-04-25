/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:48:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/25 14:02:58 by tkuhar           ###   ########.fr       */
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
	int				field;
	int				precision;
	char			size_spec;
	
	struct l_key	*next;
}					t_key;

#endif