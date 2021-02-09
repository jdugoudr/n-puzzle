/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manhattan.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 21:11:38 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MANHATTAN_HPP
# define MANHATTAN_HPP

# include "IHeuristic.hpp"

# include <string>

class Manhattan : public IHeuristic{

public:
	Manhattan();
	virtual ~Manhattan();

	virtual int						calculate(Node *current, Node *goal) const;
	virtual std::string const		getName() const;

private:
	std::string						_name;
};

#endif

