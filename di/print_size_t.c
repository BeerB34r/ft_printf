/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_size_t.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:52:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:52:39 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_size_t(t_printf_arg *argument, int *count, va_list *args)
{
	const size_t	value = va_arg(*args, size_t);
	const int		vallen = get_size_t_len(value);


}

