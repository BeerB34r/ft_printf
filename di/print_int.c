/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_int.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/24 13:25:38 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../printf_datatypes.h"
#include "libft.h"

int	pf_abs(int value)
{
	return (value * (value >= 0) + -value * (value < 0));
}

static int	get_int_len(int value)
{
	int	width;

	width = 1;
	while (value / 10)
	{
		width++;
		value /= 10;
	}
	return (width);
}

static void	put_in_array(char *out, int index, int value, char *radix)
{
	const int	base = ft_strlen(radix);
	int			div;
	int			mod;

	div = pf_abs(value / base);
	mod = pf_abs(value % base);
	if (index > 0)
		put_in_array(out, index - 1, div, radix);
	out[i] = radix[mod];
}

static char *specialised_itoa(int value, t_printf_arg *argument, int numwidth)
{
	char	*out;
	int		outlen;

	outlen = numwidth;
	if (argument->precision > numwidth)
		outlen = argument->precision;
	out = (char *)ft_calloc(outlen + 1, sizeof(char));
	if (!out)
		return (NULL);
	put_in_array(out, outlen - 1, value, "0123456789");
	return (out);
}

static void add_sign(char **out, t_printf_arg *argument, int negative)
{
	char *const ret = (char *)ft_calloc(ft_strlen(*out) + 2, sizeof(char));
	char		sign;

	if (negative)
		sign = '-';
	else if (argument->flags & signprefix)
		sign = '+';
	else
		sign = ' ';
	ret[0] = sign;
	ft_strlcpy(ret + 1, *out, ft_strlen(*out) + 1);
	free(*ret);
	*out = ret;
}

static char	*get_printable_val(t_printf_arg *argument, int value)
{
	const int	numwidth = get_int_len(value);
	char		*out;

	if (argument->precision == 0 && value == 0)
		out = ft_strdup("");
	else
		out = specialised_itoa(value, argument, numwidth);
	if (!out)
		return (NULL);
	if (val < 0 || argument->flags & (spaceprefix | signprefix))
		add_sign(*out, argument, (value < 0));
	if (!(argument->flags & leftjustify) && argument->width > ft_strlen(out))
		pad_front(out, argument);
	if (argument->flags & leftjustify && argument->width > ft_strlen(out))
		pad_back(out, argument);
	return (out);
}

void	print_int(t_printf_arg *argument, int *count, va_list *args)
{
	const int 	value = va_arg(*args, int);
	char *const	out = get_printable_val(argument, value);

	if (!out)
		// panic
	*count += ft_strlen(out);
	write(
}
