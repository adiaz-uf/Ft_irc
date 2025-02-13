/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:09:31 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/02/06 12:46:27 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP
# include "Server.hpp"

#define INVITE_ONLY         'i'
#define TOPIC_PROTECTED     't'
#define OPERATOR_TOGGLE     'o'
#define SIZE_LIMIT          'l'
#define KEY_WORD            'k'
#define ACCEPTED            true
#define DENIED              false
#define ON                   1
#define OFF                  0
#define EMPTY                ""
#define OPERTATOR            "@"

std::string aggregate(std::vector<std::string> command, int start);
std::string toUpperCase(std::string str);

#endif