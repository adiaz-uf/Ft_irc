/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:09:31 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/16 10:59:35 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP
# include "Server.hpp"

#define INVITE_ONLY      'i'
#define TOPIC_PROTECTED  't'
#define ON                1
#define OFF               0

std::string aggregate(std::vector<std::string> command, int start);

#endif