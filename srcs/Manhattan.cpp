/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 21:11:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manhattan.hpp"

Manhattan::Manhattan():
	_name("Manhattan")
{}

Manhattan::~Manhattan()
{
}

int					Manhattan::calculate(Node *current, Node *goal) const
{
	(void)current;
	(void)goal;
	return 42;
}

std::string	const	Manhattan::getName() const
{
	return _name;
}
