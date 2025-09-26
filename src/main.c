#include "cub3d.h"
#include <stdlib.h>

// base_init: t_base struct'ını başlatır
void base_init(t_base *base)
{
	base->map_info = NULL;
}

// main: programın giriş noktası, argümanları kontrol eder ve haritayı yükler
int main(int ac, char **av)
{
	t_base base;
	base_init(&base);
	if (!map_control(ac, av) || !import_map(&base, av[1]))
		exit(1);
	free_map_info(base.map_info);
	return 0;
}