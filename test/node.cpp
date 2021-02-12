/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_node.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:07:10 by jdugoudr          #+#    #+#             */
/*   Updated: 2021/02/12 22:37:18 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include <array>

using namespace std;

int	main( void )
{
	vector<int>	map = {1, 3, 2, 0, 4, 5, 7, 6, 8};

	Node	nod(map, 3);

	cout << nod;

	return 0;
}
