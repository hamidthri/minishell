/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:41:10 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/08 19:44:04 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"


int find_equal(char *str) {
    int i = 0;
    while (str[i]) {
        if (str[i] == '=') {
            return i;
        }
        i++;
    }
    return -1;
}

// int main() {
//     char *str = "export ='Hamid' ";
// 	char **str1 = ft_split(str, ' ');
//     int equalIndex = find_equal(str1[1]);

//     if (equalIndex == -1) {
//         printf("No '=' found in the string '%s'\n", str);
//     } else {
//         printf("'=' found at index %d in the string '%s'\n", equalIndex, str);
//     }

//     return 0;
// }
