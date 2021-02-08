/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Case.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 21:11:38 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CASE_HPP
# define CASE_HPP

#include <iostream>

class Case{

private:
	int const	_value;
	int				_x;
	int				_y;

	Case();
	Case(Case const &other);
	Case	&operator=(Case const &other);

public:
	Case(int value, int posX, int posY);
	virtual ~Case();

	int				getValue() const;
	int				getPosX() const;
	int				getPosY() const;

	void			setPosX(int posx);
	void			setPosY(int posy);

};

std::ostream	&operator<<(std::ostream &o, Case const &c);

#endif

