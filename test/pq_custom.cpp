/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 00:44:14 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/17 15:38:25 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pq_custom.hpp"
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>

struct	A{
	std::vector<int>	_a;
	int	_b;
	A(std::vector<int> a, int b):_a(a), _b(b){}

	bool operator==(const A &other){
		return _a == other._a;
	}

	bool operator>(const A &other) const {
		return _b > other._b;
	}
	bool operator<(const A &other) const {
		return _b < other._b;
	}	

};

bool comp(const A &a, const A &b)
{
	return a > b;
}

std::ostream	&operator<<(std::ostream &o, A const &c)
{
	o << "( {";
	for (auto it = c._a.begin() ; it != c._a.end() ; it++){
		o << *it << (std::distance(it, c._a.end()) == 1 ? "}" : ",");
	}
	o <<  " - " << c._b << " )";
	return o;
}

void	display(int a)
{
	std::cout << a << " ";
}

int main( void )
{
	pq_custom<A> pq;

	pq.push(A({1, 0}, 2));
	pq.push(A({2, 0},3));
	pq.push(A({3, 0}, 6));
	pq.push(A({4, 0}, 7));

	std::cout << pq;
	std::cout << (std::is_heap(pq.begin(),pq.end(),comp) ? "Still heap" : "No longueur heap") << std::endl;

	pq.re_push(A({4, 0}, 4));
	std::cout << pq;
	std::cout << (std::is_heap(pq.begin(),pq.end(),comp) ? "Still heap" : "No longueur heap") << std::endl;



	return 0;
}
