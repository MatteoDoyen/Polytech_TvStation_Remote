PhidgetIRHandle* CreatePhidget(char* serialNumber);
void DeletePhidget(PhidgetIRHandle *phidget);
PhidgetIR_CodeInfo Config();
void ReturnCodeFromPhidget(PhidgetReturnCode result);
PhidgetReturnCode ActionRealisedByPhidget(PhidgetIRHandle *phidget, char *action, PhidgetIR_CodeInfo PhidgetConfig);
char *AnalysisAction(char action);