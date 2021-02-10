/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_custom.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:11:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/09 22:10:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	P_QUEUE_CUSTOM_HPP
# define P_QUEUE_CUSTOM_HPP

#include "Node.hpp"
#include <queue>
#include <iostream>

//template
//bool												Node::comp(Node *a, Node *b)
//{
//	return *a > *b;
//}

template<typename T>
class p_queue_custom: public std::priority_queue<T, std::vector<T>, bool (*)(T,T)>{

private:

public:
	p_queue_custom<T>(bool (*f)(T,T)):std::priority_queue<T, std::vector<T>, bool (*)(T,T)>(f){}
	virtual ~p_queue_custom(){}
	void		push(const T& val){
		typedef typename std::priority_queue<T>::container_type::iterator	iterator;
		iterator	it;
		iterator	end;

		it = std::priority_queue<T, std::vector<T>, bool (*)(T,T)>::c.begin();
		end = std::priority_queue<T, std::vector<T>, bool (*)(T,T)>::c.end();
		while (it != end)
		{
			if (**it == *val)
				return ;
			it++;
		}
		std::priority_queue<T, std::vector<T>, bool (*)(T,T)>::push(val);
		return ;
	}
};

#endif

