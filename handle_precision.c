/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   handle_precision.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 22:27:38 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 22:29:15 by mde-beer            ########   odam.nl   */
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
		NULL,
		prepend_zero,
		prepend_zero,
		prepend_zero,
		prepend_zero,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
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
		return (!*out);
	}
	else if (format.precision > strlen((*out)->buf))
	{
		temp = calloc_fa_c(format.precision);
		if (!temp)
		{
			free(*out);
			return (1);
		}
		memset(temp->buf, '0', sizeof(char) * temp->len);
		memcpy(temp + temp->len - (*out)->len,
			(*out)->buf, sizeof(char) * (*out)->len);
		free(*out);
		*out = temp;
	}
	return (0);
}
