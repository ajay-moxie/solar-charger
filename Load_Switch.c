
#include "Load_Switch.h"

void config_load_switch (void) {
  ANSC3 = 0;
  TRISC3 = 0;
}

void enable_load_switch(void) {
  LATC3 = 0;
}

void disable_load_switch(void) {
  LATC3 = 1;
}

void configure_load_switch(void) {
  disable_load_switch();
  config_load_switch();
} 
