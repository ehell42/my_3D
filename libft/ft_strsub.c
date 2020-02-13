/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:05:36 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 11:59:35 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*strmem;

	j = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	strmem = ft_strnew(len);
	if (strmem == NULL)
		return (NULL);
	ft_strclr(strmem);
	while (j < len && s[start] != '\0')
	{
		strmem[j] = s[start];
		j++;
		start++;
	}
	return (strmem);
}
