/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   ft_printf.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/15 19:04:44 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 20:49:36 by mde-beer            ########   odam.nl   */
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

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "fa_c.h"
#include "_printf.h"

static
int
	printf_chassis(
const char *format,
va_list args,
t_fa_c **store
)
{
	t_fa_c	*out;
	t_fa_c	*temp;

	if (!*format)
		return (0);
	else if (*format == '%')
		out = handle_format(&format, args, (*store)->len);
	else
		out = handle_raw(&format);
	if (!out)
		return (1);
	temp = join_fa_c(*store, out);
	free(out);
	free(*store);
	if (!temp)
		return (1);
	*store = temp;
	return (printf_chassis(format, args, store));
}

int
	ft_snprintf(
char *buf,
size_t buf_size,
const char *format,
...
)
{
	va_list	args;
	t_fa_c	*formatted;
	int		ret;

	formatted = NULL;
	va_start(args, format);
	if (printf_chassis(format, args, &formatted))
		return (-1);
	ret = formatted->len;
	if (buf_size - 1 < formatted->len)
	{
		memcpy(buf, formatted->buf, buf_size - 1);
		buf[buf_size - 1] = 0;
	}
	else
	{
		memcpy(buf, formatted->buf, formatted->len);
		buf[formatted->len] = 0;
	}
	free(formatted);
	return (ret);
}

int
	ft_dprintf(
int fd,
const char *format,
...
)
{
	va_list	args;
	t_fa_c	*formatted;
	int		ret;

	formatted = NULL;
	va_start(args, format);
	if (printf_chassis(format, args, &formatted))
		return (-1);
	ret = write(fd, formatted->buf, formatted->len);
	free(formatted);
	return (ret);
}

int
	ft_printf(
const char *format,
...
)
{
	va_list	args;
	t_fa_c	*formatted;
	int		ret;

	formatted = NULL;
	va_start(args, format);
	if (printf_chassis(format, args, &formatted))
		return (-1);
	ret = write(STDOUT_FILENO, formatted->buf, formatted->len);
	free(formatted);
	return (ret);
}
