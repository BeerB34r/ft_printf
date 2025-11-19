/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   fa_c_alloc.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/15 20:13:44 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/18 21:43:25 by mde-beer            ########   odam.nl   */
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

#include <stdlib.h>
#include <string.h>
#include "fa_c.h"

/**
 * @brief allocates a new flexible array
 *
 * @param len length of the array
 * @return flexible array | NULL
 */
t_fa_c
	*calloc_fa_c(
unsigned int len
)
{
	t_fa_c *const	out = malloc(sizeof(t_fa_c) + sizeof(char) * len);

	if (out)
	{
		out->len = len;
		bzero(out->buf, out->len);
	}
	return (out);
}

/**
 * @brief reallocates an existing flexible array
 *
 * allocates a new block memory block in accordance with len, copies the
 * original data into the new memory block and frees the old memory
 *
 * if allocation fails, does not free @param old and returns NULL
 * @param old flexible array to be reallocated
 * @param len new length of the flexible array
 * @return flexible array | NULL
 */
t_fa_c
	*realloc_fa_c(
t_fa_c *old,
unsigned int len
)
{
	t_fa_c *const	out = calloc_fa_c(len);

	if (!old || !out)
		return (out);
	else if (out->len > old->len)
		memcpy(out->buf, old->buf, old->len);
	else
		memcpy(out->buf, old->buf, out->len);
	free(old);
	return (out);
}

/**
 * @brief joins two flexible arrays
 *
 * @param fa1 prefix flexible array
 * @param fa2 suffix flexible array
 * @return flexible array | NULL
 */
t_fa_c
	*join_fa_c(
t_fa_c *fa1,
t_fa_c *fa2
)
{
	t_fa_c			*out;
	unsigned int	first_len;
	unsigned int	second_len;

	first_len = 0;
	if (fa1)
		first_len += fa1->len;
	second_len = 0;
	if (fa2)
		second_len += fa2->len;
	out = calloc_fa_c(first_len + second_len);
	if (out)
	{
		if (fa1)
			memcpy(out->buf, fa1->buf, fa1->len);
		if (fa2)
			memcpy(out->buf + first_len, fa2->buf, fa2->len);
	}
	return (out);
}

t_fa_c
	*fa_c_from_str(
const char *str
)
{
	t_fa_c *const	out = calloc_fa_c(strlen(str));

	if (out)
		memcpy(out->buf, str, out->len);
	return (out);
}
