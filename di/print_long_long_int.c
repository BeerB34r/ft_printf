/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_long_long_int.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:51:43 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:52:03 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_long_long_int(t_printf_arg *argument, int *count, va_list *args)
{
	const long long int	value = va_arg(*args, long long int);
	const int			vallen = get_long_long_int_len(value);


}


