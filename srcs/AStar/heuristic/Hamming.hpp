/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hamming.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:48:15 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/16 22:58:07 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	HAMMING_HPP
# define HAMMING_HPP

# include "IHeuristic.hpp"

# include <string>
# include <vector>

class Hamming : public IHeuristic{

private:
	std::string				_name;

public:
	Hamming();
	virtual ~Hamming();

	virtual int					calculate(std::vector<int> const &map, Node const &goal) const;
	virtual std::string const	getName() const;

};

#endif
