/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Case.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:51:28 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 15:18:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Case.hpp"
#include <iostream>

Case::Case():_value(0)
{
}

Case::Case(Case const &other):_value(other._value)
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
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

Case::Case(int value, int posY, int posX):_value(value),
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
		<< "-" << c.getPosY()
		<< "-" << c.getPosX()
		<< "]" << std::endl;
	return o;
}

