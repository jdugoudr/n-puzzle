/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_custom.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:11:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 16:37:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	P_QUEUE_CUSTOM_HPP
# define P_QUEUE_CUSTOM_HPP

#include "Node.hpp"
#include <queue>
#include <algorithm>
#include <iostream>

template<typename T>
class p_queue_custom: public std::priority_queue<T, std::vector<T>, bool (*)(T,T)>{

private:

public:
	p_queue_custom<T>(bool (*f)(T,T)):std::priority_queue<T, std::vector<T>, bool (*)(T,T)>(f){}
	virtual ~p_queue_custom(){}


	typedef typename std::priority_queue<T, std::vector<T>, bool (*)(T,T)>::container_type::iterator	iterator;

	iterator	begin(){
		return std::priority_queue<T,
					 											std::vector<T>,
																bool (*)(T,T)>::c.begin();
	}
	iterator	end(){
		return std::priority_queue<T,
					 											std::vector<T>,
																bool (*)(T,T)>::c.end();
	}


	void		push_uniq(const T& val){
		iterator	it;
		iterator	end;

		it = this->begin();
		end = this->end();
		if (std::find(it, end, val) == end)
			this->push(val);

		return ;
	}
};

std::ostream	&operator<<(std::ostream &o, p_queue_custom<Node*> &c);

#endif

