#include "cub3d.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_base base;

    if (argc != 2)
    {
        printf("Usage: inspect_map <map.cub>\n");
        return 2;
    }
    base.map_info = NULL;
    if (!import_map(&base, argv[1]))
    {
        printf("inspect_map: import_map failed for %s\n", argv[1]);
        return 1;
    }
    t_map_info *m = base.map_info;
    printf("--- Map Info for %s ---\n", argv[1]);
    printf("north: %s\n", m->north ? m->north : "(null)");
    printf("south: %s\n", m->south ? m->south : "(null)");
    printf("west: %s\n", m->west ? m->west : "(null)");
    printf("east: %s\n", m->east ? m->east : "(null)");
    printf("floor color: %d\n", m->floor_c);
    printf("ceiling color: %d\n", m->ceiling_c);
    printf("map width: %d, height: %d\n", m->map_width, m->map_height);
    printf("map lines:\n");
    for (int i = 0; m->map && m->map[i]; i++)
        printf("[%02d] %s\n", i, m->map[i]);
    free_map_info(m);
    return 0;
}
