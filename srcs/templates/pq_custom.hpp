/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_custom.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:11:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 15:25:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	P_QUEUE_CUSTOM_HPP
# define P_QUEUE_CUSTOM_HPP

//#include "Node.hpp"
//#include <list>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
class pq_custom: public
						priority_queue<T, vector<T>, std::greater<T>>{

private:

public:
	pq_custom<T>():priority_queue<T,vector<T>,greater<T>>()
	{
	}
	virtual ~pq_custom(){}


	typedef typename priority_queue<T,vector<T>,greater<T>>::container_type::iterator	iterator;

	void	re_push(T el) {
		iterator	it = this->begin();
		iterator	end = this->end();
		iterator	newPos = end;

		for (it = this->begin() ; it != end ; it++)
		{
			if (newPos == end && *it > el)
				newPos = it;
			if (*it == el)
				break ;
		}
		if (it == end || newPos == end)
			throw std::out_of_range("Element not find in pq_custom");
		priority_queue<T,vector<T>,greater<T>>::c.erase(it);
		priority_queue<T,vector<T>,greater<T>>::c.insert(newPos, el);

	}

	iterator	begin(){
		return priority_queue<T,vector<T>,greater<T>>::c.begin();
	}
	iterator	end(){
		return priority_queue<T,vector<T>,greater<T>>::c.end();
	}

};

template<typename T>
std::ostream	&operator<<(std::ostream &o, pq_custom<T> &c)
{
	for (auto it: c)
		o << it << " ";
	o << endl;
	return o;
}

#endif

