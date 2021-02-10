/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHeuristic.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/10 19:47:34 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	IHEURISTIC_HPP
# define IHEURISTIC_HPP

#include "Node.hpp"

class IHeuristic{

public:
	virtual ~IHeuristic() {}

	virtual int					calculate(Node const &current, Node const &goal) const = 0;
	virtual std::string const	getName() const = 0;
};

#endif

