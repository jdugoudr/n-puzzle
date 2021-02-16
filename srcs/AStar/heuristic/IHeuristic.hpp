/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHeuristic.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:56:02 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	IHEURISTIC_HPP
# define IHEURISTIC_HPP

#include "Node.hpp"
#include <vector>

class IHeuristic{

public:
	virtual ~IHeuristic() {}

	virtual int					calculate(std::vector<int> const &current, Node const &goal) const = 0;
	virtual std::string const	getName() const = 0;
};

#endif

