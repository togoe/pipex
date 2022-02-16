/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctogoe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:27:08 by ctogoe            #+#    #+#             */
/*   Updated: 2022/01/26 19:47:36 by ctogoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_s;

	if (!s1 && !s2[0])
		return(NULL);
	new_s = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!new_s)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = -1;
	while (s1 && s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2 && s2[++j])
		new_s[i + j] = s2[j];
	if (s1)
		free(s1);
	return (new_s);
}