/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   handle_width.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 22:31:31 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 22:32:01 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "fa_c.h"
#include "_printf.h"

int
	pad_right(
t_fa_c **out,
int width
)
{
	const int	old_len = (*out)->len;
	t_fa_c		*temp;

	temp = realloc_fa_c(*out, width);
	if (!temp)
	{
		free(*out);
		return (1);
	}
	memset(temp->buf + old_len, ' ', temp->len - old_len);
	*out = temp;
	return (0);
}

void
	fix_sign(
t_fa_c *out,
enum e_printf_sign sign
)
{
	char	sign_char;

	sign_char = 0;
	if (sign == NEG_SIGN)
		sign_char = '-';
	else if (sign == POS_SIGN)
		sign_char = '+';
	else if (sign == SPC_SIGN)
		sign_char = ' ';
	if (sign_char)
	{
		*(char *)memchr(out->buf, sign_char, out->len) = '0';
		out->buf[0] = sign_char;
	}
}

int
	pad_zero(
t_fa_c **out,
int width,
enum e_printf_sign sign
)
{
	t_fa_c	*internal;
	t_fa_c	*temp;

	internal = calloc_fa_c(width - (*out)->len);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	memset(internal->buf, '0', internal->len);
	temp = join_fa_c(internal, *out);
	free(*out);
	free(internal);
	if (!temp)
		return (1);
	fix_sign(temp, sign);
	*out = temp;
	return (0);
}

int
	pad_left(
t_fa_c **out,
int width
)
{
	t_fa_c	*internal;
	t_fa_c	*temp;

	internal = calloc_fa_c(width - (*out)->len);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	memset(internal->buf, ' ', internal->len);
	temp = join_fa_c(internal, *out);
	free(*out);
	free(internal);
	*out = temp;
	return (!*out);
}

int
	pad_if_needed(
t_fa_c **out,
struct s_printf_argument format
)
{
	if (!format.using_width || (unsigned int)format.width <= (*out)->len)
		return (0);
	if (format.flags & MINUS)
		return (pad_right(out, format.width));
	else if (format.flags & ZERO && !format.using_precision
		&& format.specifier != SIGNED_INTEGER
		&& format.specifier != OCTAL
		&& format.specifier != HEXADECIMAL
		&& format.specifier != UNSIGNED_INTEGER
	)
	{
		free(*out);
		return (1);
	}
	else if (format.flags & ZERO && !format.using_precision)
		return (pad_zero(out, format.width, format.sign));
	return (pad_left(out, format.width));
}

int
	handle_width(
t_fa_c **out,
struct s_printf_argument format
)
{
	static int (*const	specifiers[])(t_fa_c **, struct s_printf_argument) = {
		NULL,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		pad_if_needed,
		NULL,
		pad_if_needed
	};

	if (specifiers[format.specifier])
		return (specifiers[format.specifier](out, format));
	return (0);
}
