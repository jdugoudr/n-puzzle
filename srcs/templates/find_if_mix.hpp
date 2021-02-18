/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_if_mix.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:39:01 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/11 20:44:56 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_IF_CMP_HPP
# define FIND_IF_CMP_HPP

template<class C, class T>
C	find_if_mix(C start, C end,
								T const &val, bool (*f)( T, T))
{
	while (start != end)
	{
		if (f(*start, val))
			break ;
		start++;
	}
	return start;
}

#endif
