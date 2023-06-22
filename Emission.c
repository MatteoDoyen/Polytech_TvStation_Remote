#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <phidget22.h>
#include "Config.h"
#include "Emission.h"

// Configurer les emetteurs
PhidgetIR_CodeInfo Config()
{
    PhidgetIR_CodeInfo codeInfo;
    codeInfo = (PhidgetIR_CodeInfo){
        .bitCount = 32,
        .encoding = IR_ENCODING_SPACE,
        .length = IR_LENGTH_CONSTANT,
        .gap = 108156,
        .trail = 543,
        .header = {8668, 4550},
        .one = {543, 1725},
        .zero = {543, 592},
        .repeat = {8968, 2283, 543},
        .minRepeat = 0,
        .carrierFrequency = 38000,
    };
    return codeInfo;
}

PhidgetIRHandle* CreatePhidget(char* serialNumber){
    PhidgetReturnCode res;
    PhidgetIRHandle *phidget = malloc(sizeof(int));
    res = PhidgetIR_create(phidget);
    res = Phidget_setDeviceSerialNumber((PhidgetHandle)*phidget, atoi(serialNumber));
    ReturnCodeFromPhidget(res);
    return phidget;
}

void DeletePhidget(PhidgetIRHandle *phidget){
    PhidgetIR_delete(phidget);
    free(phidget);
}

PhidgetReturnCode ActionRealisedByPhidget(PhidgetIRHandle *phidget, char *action, PhidgetIR_CodeInfo phidgetConfig){
    PhidgetReturnCode res;
    char *phidgetCommand;
    res = Phidget_openWaitForAttachment((PhidgetHandle)*phidget, PHIDGET_TIMEOUT_DEFAULT);
    ReturnCodeFromPhidget(res);
    phidgetCommand = action;
    res = PhidgetIR_transmit(*phidget, phidgetCommand, &phidgetConfig);
    ReturnCodeFromPhidget(res);
    return res;
}

// Tester si l'action s'est correctement déroulé
void ReturnCodeFromPhidget(PhidgetReturnCode result)
{
    if (result != EPHIDGET_OK)
    {
        printf("Error phidget %x\n", result);
        exit(-1);
    }
}

// Analyser l'action et transmettre la commande correspondante
char *AnalysisAction(char action)
{
    char *select;
    switch (action)
    {
    case '0':
        select = command_0;
        break;
    case '1':
        select = command_1;
        break;
    case '2':
        select = command_2;
        break;
    case '3':
        select = command_3;
        break;
    case '4':
        select = command_4;
        break;
    case '5':
        select = command_5;
        break;
    case '6':
        select = command_6;
        break;
    case '7':
        select = command_7;
        break;
    case '8':
        select = command_8;
        break;
    case '9':
        select = command_9;
        break;
    case '+':
        select = command_VolumePlus;
        break;
    case '-':
        select = command_VolumeMinus;
        break;
    case 'o':
        select = command_Ok;
        break;
    case 'p':
        select = command_Power;
        break;
    case 'e':
        select = command_EscExit;
        break;
    case 'm':
        select = command_Mute;
        break;
    case 'u':
        select = command_Up;
        break;
    case 'd':
        select = command_Down;
        break;
    case 'r':
        select = command_Right;
        break;
    case 'l':
        select = command_Left;
        break;
    case 'M':
        select = command_Menu;
        break;
    case 'x':
        select = command_CHMinus;
        break;
    case 'y':
        select = command_CHPlus;
        break;
    case 't':
        select = command_ST ; 
    default:
        break;
    }
    return select;
}