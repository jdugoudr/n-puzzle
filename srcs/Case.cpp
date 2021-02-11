/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Case.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/11 20:18:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Case.hpp"
#include <iostream>

Case::Case():_value(0)
{
}

Case::Case(Case const &other):_value(0)
{
	*this = other;
}

Case::~Case()
{
}

Case	&Case::operator=(Case const &other)
{
	if (this != &other)
	{
		//put here whatever make your object equal to an other
	}
	return *this;
}

Case::Case(int value, int posX, int posY):_value(value),
																					_x(posX),
																					_y(posY)
{}

int				Case::getValue() const
{
	return _value;
}

int				Case::getPosX() const
{
	return _x;
}

int				Case::getPosY() const
{
	return _y;
}

void			Case::setPosX(int posx)
{
	_x = posx;
	return ;
}

void			Case::setPosY(int posy)
{
	_y = posy;
	return ;
}

bool			Case::operator!=(Case const &other) const
{
	return _value != other._value;
}

bool			Case::operator==(Case const &other) const
{
	return _value == other._value;
}

bool			Case::compare_ptr(Case *a, Case *b)
{
//	std::cout << "compare : "
//						<< a->getValue() << b->getValue()
//						<< std::endl
//						<< *a << *b ;
	return *a == *b;
}


std::ostream	&operator<<(std::ostream &o, Case const &c)
{
	o << "[" << c.getValue()
		<< "-" << c.getPosX()
		<< "-" << c.getPosY()
		<< "]" << std::endl;
	return o;
}

