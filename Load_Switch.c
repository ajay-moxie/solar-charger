
#include "Load_Switch.h"

/*void config_load_switch (void) {
  ANSC3 = 0;
  TRISC3 = 0;
}*/

void enable_load_switch(void) {
  LATC3 = 0;
}

void disable_load_switch(void) {
  LATC3 = 1;
}

void load_switch_init(void) {
  disable_load_switch();
  ANSC3 = 0;
  TRISC3 = 0;
} 

void load_switch_exit(void)
{
  disable_load_switch();
  ANSC3 = 1;
  TRISC3 = 1;

}
