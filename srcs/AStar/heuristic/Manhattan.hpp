/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 22:29:06 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MANHATTAN_HPP
# define MANHATTAN_HPP

# include "IHeuristic.hpp"

# include <string>

class Manhattan : public IHeuristic{

private:
	std::string				_name;

//	int								calculDiff(int curr, int goal) const;

public:
	Manhattan();
	virtual ~Manhattan();

	virtual int					calculate(Node const &current, Node const &goal) const;
	virtual std::string const		getName() const;

};

#endif

