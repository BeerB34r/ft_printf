/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ftprintf_signed_decimal.h                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 18:44:00 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/21 19:05:42 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_SIGNED_DECIMAL_H
# define FTPRINTF_SIGNED_DECIMAL_H

void	print_int(t_printf_arg *argument, int *count, va_list *args);
void	print_signed_char(t_printf_arg *argument, int *count, va_list *args);
void	print_short_int(t_printf_arg *argument, int *count, va_list *args);
void	print_long_int(t_printf_arg *argument, int *count, va_list *args);
void	print_long_long_int(t_printf_arg *argument, int *count, va_list *args);
void	print_intmax(t_printf_arg *argument, int *count, va_list *args);
void	print_size_t(t_printf_arg *argument, int *count, va_list *args);
void	print_ptrdiff(t_printf_arg *argument, int *count, va_list *args);

#endif
