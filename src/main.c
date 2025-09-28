#include "cub3d.h"
#include <stdlib.h>


// base_init: t_base struct'ını başlatır
void	base_init(t_base *base)
{
	base->map_info = NULL;
}

// main: programın giriş noktası, argümanları kontrol eder ve haritayı yükler
int	main(int ac, char **av)
{
	t_base base;
	base_init(&base);
	if (!map_control(ac, av) || !import_map(&base, av[1]))
		exit(1);
	main_loop(&base);
	free_map_info(base.map_info);
	return (0);
}

int	main_loop(t_base *game)
{
	// Zemin ve tavanı çiz (düz renk)
	draw_floor_ceiling(game);

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		// 1. Işın yönünü ve başlangıç değişkenlerini hesapla
		calculate_ray_position_and_direction(game, x);

		// 2. DDA için başlangıç adımlarını ve mesafeleri hesapla
		calculate_step_and_initial_sidedist(game);

		// 3. DDA algoritmasını çalıştırarak duvara çarp
		perform_dda(game);

		// 4. Dik mesafeyi ve duvar yüksekliğini hesapla
		calculate_perp_wall_dist_and_line_height(game);

		// 5. Çizim sınırlarını belirle
		calculate_draw_start_and_end(game);

		// 6. Doku koordinatlarını hesapla
		calculate_texture_coordinates(game);

		// 7. Dikey duvar dilimini görüntü arabelleğine çiz
		draw_vertical_line_to_buffer(game, x);
	}

	// (İsteğe bağlı) Sprite'ları çiz
	// draw_sprites(game);

	// Görüntü arabelleğini pencereye aktar
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

	return (0);
}