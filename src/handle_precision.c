/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   handle_precision.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 22:27:38 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/19 04:45:36 by mde-beer            ########   odam.nl   */
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

static int	prepend_zero(t_fa_c **out, struct s_printf_argument format);
static int	truncate(t_fa_c **out, struct s_printf_argument format);

// As a reminder, the format specifiers enum is in the following order:
// PERCENT
// CHARACTER
// STRING
// SIGNED_INTEGER
// OCTAL
// HEXADECIMAL
// UNSIGNED_INTEGER
// FLOAT
// DECIMAL_EXPONENT
// HEXADECIMAL_EXPONENT
// HEURISTIC_FLOAT
// STORE
// POINTER

int
	handle_precision(
t_fa_c **out,
struct s_printf_argument format
)
{
	static int (*const	specifiers[])(t_fa_c **, struct s_printf_argument) = {
		NULL,
		NULL,
		truncate,
		prepend_zero,
		prepend_zero,
		prepend_zero,
		prepend_zero,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		prepend_zero
	};

	if (specifiers[format.specifier])
		return (specifiers[format.specifier](out, format));
	return (0);
}

static
int
	prepend_zero(
t_fa_c **out,
struct s_printf_argument format
)
{
	t_fa_c	*temp;

	if (!format.precision && (*out)->buf[0] == '0')
	{
		temp = realloc_fa_c(*out, 0);
		if (!temp)
			free(*out);
		*out = temp;
	}
	else if ((unsigned int)format.precision > (*out)->len)
	{
		temp = calloc_fa_c(format.precision);
		if (!temp)
		{
			free(*out);
			return (1);
		}
		memset(temp->buf, '0', sizeof(char) * temp->len);
		;
		;
		;
		if ((*out)->len)
			memcpy(temp + temp->len - (*out)->len - 1, (*out)->buf, sizeof(char) * (*out)->len);
		free(*out);
		*out = temp;
	}
	return (!*out);
}

static
int
	truncate(
t_fa_c **out,
struct s_printf_argument format
)
{
	t_fa_c	*temp;

	if (!format.using_precision)
		return (0);
	if (format.null && format.precision < 6)
		format.precision = 0;
	else if (format.null || (unsigned int)format.precision >= (*out)->len)
		return (0);
	temp = realloc_fa_c(*out, format.precision);
	if (!temp)
	{
		free(*out);
		return (1);
	}
	*out = temp;
	return (0);
}
