#ifndef SERVER_H
#define SERVER_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Coms/Coms.h"
#include "Game/Game.h"
#include "Utils/Utils.h"

/* Defines */
#define VERSION "0.1"

/* Prototypes */
int Serv_Setup(void);      //Server setup function

#endif
