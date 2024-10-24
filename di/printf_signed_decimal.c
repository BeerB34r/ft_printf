/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_signed_decimal.c                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:50:12 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdarg.h>

void	print_signed_decimal(t_printf_arg *argument, int *count, va_list *args)
{
	if (argument->length == none)
		print_int(argument, count, args);
	if (argument->length == hh)
		print_signed_char(argument, count, args);
	if (argument->length == h)
		print_short_int(argument, count, args);
	if (argument->length == l)
		print_long_int(argument, count, args);
	if (argument->length == ll)
		print_long_long_int(argument, count, args);
	if (argument->length == j)
		print_intmax(argument, count, args);
	if (argument->length == z)
		print_size_t(argument, count, args);
	if (argument->length == t)
		print_ptrdiff(argument, count, args);
}
