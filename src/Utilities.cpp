/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:52:11 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/16 06:19:53 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utilities.hpp"

std::string aggregate(std::vector<std::string> command, int start_index)
{
    std::string ret = "";
    int         iterator = start_index;
    while (iterator < (int)command.size())
    {
        if (iterator != start_index)
            ret.append(" ");
        ret.append(command[iterator]);
        iterator++;
    }
    return (ret);
}