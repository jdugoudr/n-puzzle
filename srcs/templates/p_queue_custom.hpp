/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_custom.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:11:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/15 23:38:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	P_QUEUE_CUSTOM_HPP
# define P_QUEUE_CUSTOM_HPP

#include "Node.hpp"
#include <list>
#include <algorithm>
#include <iostream>

template<typename T>
class p_queue_custom: public std::list<T>{

private:
	bool	(*comp)(T,T);

public:
	p_queue_custom<T>(bool (*f)(T,T)):std::list<T>()
	{
		comp = f;
	}
	virtual ~p_queue_custom(){}


	typedef typename std::list<T>::iterator	iterator;
//
//	iterator	begin(){
//		return std::priority_queue<T,
//					 											std::vector<T>,
//																bool (*)(T,T)>::c.begin();
//	}
//	iterator	end(){
//		return std::priority_queue<T,
//					 											std::vector<T>,
//																bool (*)(T,T)>::c.end();
//	}

	bool	try_insert(const T &val, iterator &pos) {
		iterator	it;
		iterator	end = this->end();

		pos = end;
		for (it = this->begin() ; it != end ; it++)
		{
			if (pos == end && comp(val, *it))
				pos = it;
			if (*it == val)
			{
				pos = it;
				return false;
			}
		}
		return true;
	}

	void		push_uniq(const T& val){
		iterator	it;
		iterator	position;
		iterator	end;

		end = this->end();
		position = end;
		for (it = this->begin() ; it != end ; it++)
		{
			if (position == end && comp(val, *it))
				position = it;
			if (val == *it)
				return ;
		}
		this->insert(position, val);

		return ;
	}

	void		pop(){
		this->pop_front();
	}

	T				&top(){
		return this->front();
	}
};

std::ostream	&operator<<(std::ostream &o, p_queue_custom<Node*> &c);

#endif

