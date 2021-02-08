/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:07:10 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/08 22:15:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include "Case.hpp"
#include <array>

using namespace std;

int	main( void )
{
	Case	a(1, 0, 0);
	Case	b(2, 1, 0);
	Case	c(3, 0, 1);
	Case	d(0, 1, 1);

	array<Case *, 2>	l1 = {&a, &c};
	array<Case *, 2>	l2 = {&b, &d};

	array<array<Case *, 2>, 2>	map = {l1, l2};

	cout << map;

	return 0;
}
