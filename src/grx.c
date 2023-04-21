/*
 * Copyright (c) 2023 Gembera Team
 * https://github.com/gembera
 * License: MIT
 */

#include "grx.h"
#include <stdio.h>
#include <assert.h>
#include "glib.h"

void g_rx_start(){
    gint i = 100;
    //assert(i > 100);
    printf("Rx Start! i = %d", i);
}