/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/18 17:37:42 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

int     main() {
    srand(time(NULL));

    // std::string title("Nibble");
    
    // char * cstr = new char [title.length()+1];
    // std::strcpy (cstr, title.c_str());

    // void *mlx = mlx_init();
    // void *win = mlx_new_window(mlx, 500, 500, cstr);
    // void *image = mlx_new_image(mlx, 500, 500);

    // int bit, size, end;
    // char *data = mlx_get_data_addr(image, &bit, &size, &end);
    
    // for (unsigned int i = 0; i < 500; i++) {
    //     data[i * size + i * bit / 8] = 40;
    //     data[i * size + i * bit / 8 + 1] = 100;
    //     data[i * size + i * bit / 8 + 2] = -86;
    // }

    // mlx_put_image_to_window(mlx, win, image, 0, 0);

    MlxDisplay mlx = MlxDisplay(10, 10);

    std::vector<Vec2> v;
    mlx.display(v, v);
    
    // mlx_loop(mlx);
    
    return 0;
}