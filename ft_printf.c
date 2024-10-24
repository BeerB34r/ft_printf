/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 16:27:29 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/24 14:08:37 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdarg.h>

void	parse_flag(t_printf_arg *argument, char **format)
{
	while (ft_isinset(**format, FLAGS) != -1)
	{
		if (**format == '-')
			argument->flags |= leftjustify;
		if (**format == '#')
			argument->flags |= baseprefix;
		if (**format == ' ')
			argument->flags |= spaceprefix;
		if (**format == '+')
			argument->flags |= signprefix;
		if (**format == '0')
			argument->flags |= zeropad;
		(*format)++;
	}
}

void	parse_width(t_printf_arg *argument, char **format)
{
	if (**format == '*')
	{
		argument->parameter_width = true;
		(*format)++;
		return ;
	}
	if (ft_isdigit(**format))
	{
		argument->parameter_width = false;
		argument->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
}

void	parse_precision(t_printf_arg *argument, char **format)
{
	if (**format != '.')
		return ;
	(*format)++;
	if (**format == '*')
	{
		argument->parameter_width = true;
		(*format)++;
		return ;
	}
	if (ft_isdigit(**format))
	{
		argument->parameter_precision = false;
		argument->precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
}

void	parse_length(t_printf_arg *argument, char **format)
{
	if (ft_isinset(**format, LENGTH) == -1)
		return ;
	if (**format == 'h')
		argument->length = h;
	if (**format == 'l')
		argument->length = l;
	if (**format == 'j')
		argument->length = j;
	if (**format == 'z')
		argument->length = z;
	if (**format == 't')
		argument->length = t;
	if (**format == 'L')
		argument->length = u_l;
	(*format)++;
	if (argument->length == l)
		if (**format == 'l')
			argument->length = ll;
	if (argument->length == h)
		if (**format == 'h')
			argument->length = hh;
	if (argument->length == ll || argument->length == hh)
		(*format)++;
}

void	parse_specifier(t_printf_arg *argument, char **format)
{
	const t_printf_spec	specifier = ft_isinset(**format, SPECIFIER);

	if (specifier == 0)
		++specifier;
	argument->specifier = specifier;
	(*format)++;
}

void	parse_arg(t_printf_arg *argument, char **format)
{
	(*format)++;
	parse_flag(argument, format);
	parse_width(argument, format);
	parse_precision(argument, format);
	parse_length(argument, format);
	parse_specifier(argument, format);
}

void	clear_arg(t_printf_arg *argument)
{
	argument->flags = noflag;
	argument->parameter_width = maybe;
	argument->width = 0;
	argument->parameter_precision = maybe;
	argument->precision = 1;
	argument->length = none;
	argument->specifier = no_specifier;
}

void	print_type(t_printf_arg *argument, int *count, va_list *args)
{
	g_specifiers[argument->specifier - 1](argument, count, args);
}

void	print_argument(t_printf_arg *argument, int *count, va_list *args)
{
	if (argument->parameter_width == True)
		argument->width = va_arg(*args, unsigned int);
	if (argument->parameter_precision == True)
		argument->precision = va_arg(*args, unsigned int);
	print_type(argument, count, args);
}

int	ft_printf_chassis(int fd, char *format, va_list *args)
{
	int				count;
	t_printf_arg	argument;

	count = 0;
	while (*format)
	{
		if (*format != '%')
			count += print_to_arg(fd, &format);
		else
		{
			clear_arg(&argument);
			parse_arg(&argument, &format);
			print_argument(fd, &argument, &count, args);
		}
	}
	return (count);
}

int	ft_printf_fd(int fd, char *format, ...)
{
	va_list	args;

	va_start(args, format);
	return (ft_printf_chassis(fd, format, &args));
}

int	ft_printf(char *format, ...)
{
	va_list	args;

	va_start(args, format);
	return (ft_printf_chassis(0, format, &args));
}
