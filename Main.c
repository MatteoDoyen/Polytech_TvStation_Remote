#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include "phidget22.h"
#include "Config.h"
#include "Emission.h"

int CheckArguments(int argc, char **argv)
{
    if (argc < 3 || argc > 3 || strlen(argv[1]) > 6 || strlen(argv[1]) < 6)
    {
        printf("La telecommande attend 2 arguments\n");
        printf("Le premier est le numero de serie de l'emetteur IR long de 6 chiffres compris entre 0 et 9\n");
        printf("Le second est l'action a transmettre (chaine de 0 a 9999)\n");
        printf("ou commande {+,-,y,x,p,m,o,e,M,u,d,r,l,t} (vol+,vol-,ch+,ch-,power,mute,ok,exit,Menu,up,down,right,left,sub-title)\n");
        exit(-1);
    }

    char *cmd1 = argv[1];
    for (int k = 0; k < strlen(argv[1]); k++)
    {
        char *cmdk = malloc(1 * sizeof(char));
        cmdk[0] = *(cmd1 + k);
        if (strstr("0123456789", cmdk) == NULL)
        {
            printf("Le numero de serie de l'emetteur IR est long de 6 chiffres compris entre 0 et 9\n");
            exit(-1);
        }
        free(cmdk);
    }

    char *cmd = argv[2];
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        char *cmdi = malloc(1 * sizeof(char));
        cmdi[0] = *(cmd + i);
        if (strstr("poemrdluMxy-+t", cmdi) == NULL)
        {
            for (int j = 0; j < strlen(argv[2]); j++)
            {
                char *cmdj = malloc(1 * sizeof(char));
                cmdj[0] = *(cmd + j);
                if (strstr("0123456789", cmdj) == NULL)
                {
                    printf("L'action a transmettre doit etre une chaine de 0 a 9999\n");
                    printf("ou commande {+,-,y,x,p,m,o,e,M,u,d,r,l,t} (vol+,vol-,ch+,ch-,power,mute,ok,exit,Menu,up,down,right,left,sub-title)\n");
                    exit(-1);
                }
                free(cmdj);
            }
            return 0;
        }
        free(cmdi);
    }
    return 0;
}

void Delay()
{
    struct timespec ts = {0, 100000000L};
    nanosleep(&ts, NULL);
}

// Differencier les actions à réaliser en fonction de la longueur du second argument
char **GetActions(char **argv)
{
    char **actions = malloc(sizeof(char *) * strlen(argv[2]));
    for (int i = 0; i < strlen(argv[2]); i++)
    {
        actions[(strlen(argv[2]) - 1) - i] = AnalysisAction(argv[2][i]);
    }
    return actions;
}

// Telecommande 1 tuner return 0 si good , error phidget si not good
int main(int argc, char **argv)
{
    // accents console
    setlocale(LC_ALL, "");
    CheckArguments(argc, argv);
    int numberOfAction = strlen(argv[2]);
    char** actions = GetActions(argv);
    PhidgetIRHandle *phidget = CreatePhidget(argv[1]);
    PhidgetIR_CodeInfo codeInfo = Config();
    for (int i = 0; i < numberOfAction; i++)
    {
        ActionRealisedByPhidget(phidget, actions[numberOfAction - i - 1], codeInfo);
        if (i > 0)
        {
            Delay();
        }
    }
    DeletePhidget(phidget);
    return 0;
}