/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   handle_format.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 20:24:56 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/18 20:15:52 by mde-beer            ########   odam.nl   */ /*                                                                            */ /*   —————No norm compliance?——————                                           */
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

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "fa_c.h"
#include "_printf.h"

static
void
	add_formatting(
t_fa_c **out,
struct s_printf_argument format
)
{
	unsigned int	i;

	if (format.specifier == STORE || format.specifier == PERCENT)
		return ;
	if (handle_precision(out, format))
		return ;
	if (handle_sign(out, format))
		return ;
	if (handle_width(out, format))
		return ;
	i = -1;
	if (format.uppercase)
		while (++i < (*out)->len)
			(*out)->buf[i] = toupper((*out)->buf[i]);
}

static
t_fa_c
	*get_formatted(
struct s_printf_argument format,
va_list	args,
unsigned int current_len
)
{
	static t_fa_c *(*const	specifiers[])(
			va_list, unsigned int, struct s_printf_argument *) = {
		specifier_percent,
		specifier_character,
		specifier_string,
		specifier_signed_integer,
		specifier_octal,
		specifier_hexadecimal,
		specifier_unsigned_integer,
		specifier_float,
		NULL,
		NULL,
		NULL,
		specifier_store,
		specifier_pointer
	};
	t_fa_c					*out;

	out = NULL;
	if (specifiers[format.specifier])
		out = specifiers[format.specifier](args, current_len, &format);
	if (out)
		add_formatting(&out, format);
	return (out);
}

static
t_fa_c
	*handle_raw_format(
const char **format
)
{
	t_fa_c				*out;
	const char *const	next_percent = strchr(*format + 1, '%');

	if (next_percent)
		out = calloc_fa_c(next_percent - *format);
	else
		out = calloc_fa_c(strlen(*format));
	if (!out)
		return (NULL);
	memcpy(out->buf, *format, out->len);
	*format += out->len;
	return (out);
}

static
int
	default_precision(
enum e_printf_specifier type
)
{
	if (type == SIGNED_INTEGER || type == OCTAL || type == HEXADECIMAL
		|| type == UNSIGNED_INTEGER)
		return (1);
	else if (type == FLOAT)
		return (6);
	return (0);
}

t_fa_c
	*handle_format(
const char **format,
va_list args,
unsigned int current_len
)
{
	struct s_printf_argument	arg;
	const char *const			specifier = parse_argument(*format + 1, &arg);

	if (!specifier)
		return (handle_raw_format(format));
	if (arg.invalid)
		return (NULL);
	if (arg.w_arg)
		arg.width = va_arg(args, int);
	if (arg.p_arg)
		arg.precision = va_arg(args, int);
	else if (!arg.using_precision)
		arg.precision = default_precision(arg.specifier);
	*format = strchr(*format + 1, *specifier) + 1;
	if (isupper(*specifier))
		arg.uppercase = true;
	return (get_formatted(arg, args, current_len));
}
