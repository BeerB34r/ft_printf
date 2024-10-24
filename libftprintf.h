/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   libftprintf.h                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 17:30:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/24 10:41:13 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "printf_datatypes.h"

static void (*const	g_specifiers[18])(t_printf_arg *, int *, va_list *) = {
	print_signed_decimal,
	print_unsigned_decimal,
	print_unsigned_octal,
	print_unsigned_lohex,
	print_unsigned_hihex,
	print_float_dec_lo,
	print_float_dec_hi,
	print_scientific_lo,
	print_scientific_hi,
	print_short_fe_lo,
	print_short_fe_hi,
	print_float_hex_lo,
	print_float_hex_hi,
	print_character,
	print_string,
	print_pointer_adr,
	print_store_print,
	print_percent
};

// Porcelain functions
int		ft_printf(char *format, ...);
int		ft_printf_fd(int fd, char *format, ...);
int		ft_printf_chassis(int fd, char *format, va_list *args);
// Content plumbing
int		print_to_arg(int fd, char **format);
void	print_argument(t_printf_arg *argument, int *count, va_list *args);
int		get_content_len(t_printf_arg *argument, va_list *args);
void	print_type(t_printf_arg *argument, va_list *args);
int		print_front_pad(t_printf_arg *argument, va_list *args, int content_len);
int		print_back_pad(t_printf_arg *argument, va_list *args, int content_len);
// Type-specific content length plumbing

// Type-specific content print plumbing

// Argument plumbing
void	clear_arg(t_printf_arg *argument);
void	parse_arg(t_printf_arg *argument, char **format);
void	parse_flag(t_printf_arg *argument, char **format);
void	parse_width(t_printf_arg *argument, char **format);
void	parse_precision(t_printf_arg *argument, char **format);
void	parse_length(t_printf_arg *argument, char **format);
void	parse_specifier(t_printf_arg *argument, char **format);
#endif
