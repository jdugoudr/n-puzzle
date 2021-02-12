/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Case.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 15:18:20 by jdugoudr         ###   ########.fr       */
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

public:
	Case(Case const &other);
	Case(int value, int posY, int posX);
	virtual ~Case();

	Case	&operator=(Case const &other);

	bool			operator!=(Case const &other) const;
	bool			operator==(Case const &other) const;

	int				getValue() const;
	int				getPosX() const;
	int				getPosY() const;

	void			setPosX(int posx);
	void			setPosY(int posy);

	static bool	compare_ptr(Case *a, Case *b);

};

std::ostream	&operator<<(std::ostream &o, Case const &c);

#endif

