/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyu <slyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:04:50 by slyu              #+#    #+#             */
/*   Updated: 2022/09/01 22:04:51 by slyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	mouse_hook(int bttn, int x, int y, t_mlx_data *mlx_data)
{
	static int	zoom = 0;
	double		scale;
	int			pix_start[2];
	int			pix_end[2];

	if (bttn == WHEEL_UP || bttn == WHEEL_D)
	{
		if (zoom >= __INT_MAX__ || zoom <= -__INT_MAX__ - 1)
			return (-1);
		scale = pow(ZOOM_RATE, zoom);
		mlx_data->complex_num.n_start[0] += (1.0 - pow(ZOOM_RATE, pow(-1,
						bttn == WHEEL_D))) * x * ((INI_WIDTH / SIZE_X) * scale);
		mlx_data->complex_num.n_start[1] += (1.0 - pow(ZOOM_RATE, pow(-1,
						bttn == WHEEL_D))) * y * ((INI_HIGHT / SIZE_Y) * scale);
		zoom += pow(-1, bttn == WHEEL_D);
		scale = pow(ZOOM_RATE, zoom);
		mlx_data->complex_num.space[0] = scale * (INI_WIDTH / SIZE_X);
		mlx_data->complex_num.space[1] = scale * (INI_HIGHT / SIZE_Y);
		set_default_pix_se(pix_start, pix_end);
		make_image(mlx_data, pix_start, pix_end);
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win,
			mlx_data->imgdata.img, 0, 0);
	}
	return (0);
}

int	key_exit(int keycode, void *param)
{
	(void)param;
	(void)keycode;
	exit(0);
}

void	set_default_pix_se(int *pix_start, int *pix_end)
{
	pix_start[0] = 0;
	pix_start[1] = 0;
	pix_end[0] = SIZE_X;
	pix_end[1] = SIZE_Y;
}

int	key_hook(int key, t_mlx_data *mlx_data)
{	
	int			pix_start[2];
	int			pix_end[2];

	if (L_ARROW == key || key == D_ARROW || key == U_ARROW || key == R_ARROW)
	{
		if (key == L_ARROW || key == R_ARROW)
			move_x(key, mlx_data);
		else
			move_y(key, mlx_data);
	}
	else if (key == TAB)
	{
		get_color(0, 0);
		set_default_pix_se(pix_start, pix_end);
		make_image(mlx_data, pix_start, pix_end);
	}
	else if (key == ESC)
	{
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		exit(0);
	}
	if ((L_ARROW <= key && key <= U_ARROW) || key == TAB)
		mlx_put_image_to_window(mlx_data->mlx, mlx_data->win,
			mlx_data->imgdata.img, 0, 0);
	return (0);
}

int	converse_iter(t_newton *nt, int idx)
{
	return (floor(MAXITER / (double)(nt->degree) * (double)(idx + 1)));
}