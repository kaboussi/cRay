//
// Created by redone on 7/29/23.
//

#include "cray.h"

/*
 * 1 -> only 6 possible characters (0, 1, N, S, E, W) and \0
 * 2 -> only one player position
 * 3 -> surrounded by walls (1)
 * 4 -> each space should be surrounded by walls (1) or spaces
 * 5 -> each 0 should be surrounded by walls (1) or other (0)
 */

void check_borders(char *line);
void check_wholes(t_map_info *pInfo, char **line, int row, int column);

void check_map(t_map_info *pInfo, char **pString) {
    int i;
    int j;
    bool isPlayerFound;

    isPlayerFound = false;
    i = -1;
    while (pString[++i]) {
        j = -1;
        while (pString[i][++j]) {
            if (ft_strchr("01NEWS ", pString[i][j]) == NULL)
                fatal("Map contains invalid characters");
            if (ft_strchr("NEWS", pString[i][j]) != NULL) {
                if (isPlayerFound == true)
                    fatal("Map contains more than one player");
                isPlayerFound = true;
            }
            check_borders(pString[i]);
            if (pString[i][j] == '0')
                check_wholes(pInfo, pString, i, j);
        }
    }
}

void check_borders(char *line) {
    char *trimed_line;

    trimed_line = ft_strtrim(line, " ");
    if (trimed_line[0] != '1' || trimed_line[ft_strlen(trimed_line) - 1] != '1')
        fatal("Map is not surrounded by walls");
    free(trimed_line);
    trimed_line = NULL;
}

void check_wholes(t_map_info *pInfo, char **line, int row, int column) {
    if (row == 0 || row == pInfo->map_height - 1)
        fatal("Map is not surrounded by walls");
    if (column == 0 || column == pInfo->map_width - 1)
        fatal("Map is not surrounded by walls");
    if (line[row - 1][column] == ' ' || line[row + 1][column] == ' ')
        fatal("Map contains wholes");
    if (line[row][column - 1] == ' ' || line[row][column + 1] == ' ')
        fatal("Map contains wholes");
}
