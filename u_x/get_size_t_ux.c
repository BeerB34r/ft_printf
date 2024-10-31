/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_size_t_ux.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 16:09:18 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_ux.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

static void	put_array(t_uchar *out, t_uint index, \
						size_t value, char *radix)
{
	const t_uint	base = ft_strlen(radix);
	size_t			div;
	size_t			mod;

	div = value / base;
	mod = value % base;
	if (index > 0)
		put_array(out, index - 1, div, radix);
	out[index] = radix[mod];
}

static t_uchar	*pf_itoa(size_t value, t_printf_arg *argument, \
							t_uint numwidth)
{
	t_uchar	*out;
	t_uint	outlen;

	outlen = numwidth;
	if (argument->parameter_precision != maybe \
		&& argument->precision > numwidth)
		outlen = argument->precision;
	else if (argument->parameter_precision == maybe \
			&& argument->width > numwidth \
			&& argument->flags & zeropad \
			&& !(argument->flags & leftjustify))
	{
		outlen = argument->width;
		if (argument->flags & baseprefix && outlen > 1)
			outlen -= 2;
		if (outlen < numwidth)
			outlen = numwidth;
	}
	out = (t_uchar *)ft_calloc(outlen + 1, sizeof(t_uchar));
	if (!out)
		return (NULL);
	put_array(out, outlen - 1, value, "0123456789ABCDEF");
	return (out);
}

static t_uint	get_len(size_t value)
{
	t_uint	width;

	width = 1;
	while (value / 16)
	{
		width++;
		value /= 16;
	}
	return (width);
}

t_uchar	*get_z_ux(t_printf_arg *argument, size_t value)
{
	const t_uint	numwidth = get_len(value);
	t_uchar			*out;

	if (argument->precision == 0 && value == 0)
		out = (t_uchar *)ft_strdup("");
	else
		out = pf_itoa(value, argument, numwidth);
	if (!out)
		return (NULL);
	if (argument->flags & baseprefix && value > 0)
		if (add_base_ux(&out))
			return (NULL);
	if (argument->width > ft_strlen((char *)out))
		if (pad_ux(&out, argument))
			return (free(out), NULL);
	return (out);
}
