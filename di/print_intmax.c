/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_intmax.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:52:05 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:52:21 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_intmax(t_printf_arg *argument, int *count, va_list *args)
{
	const intmax_t	value = va_arg(*args, intmax_t);
	const int		vallen = get_intmax_len(value);


}


