#include <stdio.h>
#include <stdlib.h>

void loaddata_stage(uint stagedata[][22][32])
{
    FILE *datafile = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    char line[129], temp[4], line2[61];
    temp[3] = 0;

    /* Loading file */
    datafile = fopen("data/map.txt", "r");
    fgets (line, 129, datafile);
    fgets (line, 129, datafile);

    /* Cargamos los datos del fichero en el array */
    for (i = 0; i <= 24; i++) {
        for (j = 0; j <= 21; j++) {
            for (k = 0; k <= 31; k++) {
                temp[0] = line[k * 4];
                temp[1] = line[(k * 4) + 1];
                temp[2] = line[(k * 4) + 2];
                sscanf (temp, "%d", &stagedata[i][j][k]);
            }

            fgets (line, 129, datafile);
        }

        fgets (line, 129, datafile);
    }

    /* Cerramos fichero */
    fclose (datafile);
}

void loaddata_enemies(int enemydata[][7][15])
{
    FILE *datafile = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    char temp[4];
    char line2[61];

    temp[3] = 0;

    datafile = fopen("data/enemies.txt", "r");
    fgets (line2, 61, datafile);
    fgets (line2, 61, datafile);

    /* Cargamos los datos del fichero en el array */
    for (i = 0; i <= 24; i++) {
        for (j = 0; j < 7; j++) {
            for (k = 0; k < 15; k++) {
                temp[0] = line2[k * 4];
                temp[1] = line2[(k * 4) + 1];
                temp[2] = line2[(k * 4) + 2];
                sscanf (temp, "%d", &enemydata[i][j][k]);
            }

            fgets (line2, 61, datafile);
        }

        fgets (line2, 61, datafile);
    }

    fclose (datafile);
}
