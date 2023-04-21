#include "glib.h"
#include "grx.h"
#include <assert.h>

int test_rx(int, char *[]) {
  g_mem_record(g_mem_record_default_callback);
  g_mem_record_begin();

  g_rx_start();

  gulong allocated = 0;
  gulong freed = 0;
  gulong peak = 0;
  g_mem_profile(&allocated, &freed, &peak);
  g_mem_record_end();
  printf("\nallocated memory: %d  \nfreed memory: %d\npeak memory: %d\n",
         allocated, freed, peak);
  assert(allocated == freed);
  return 0;
}
