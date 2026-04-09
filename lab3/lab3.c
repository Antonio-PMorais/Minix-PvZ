#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"

extern uint32_t sys_inb_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t bit_no;
  int ipc_status;
  message msg;
  
  uint8_t bytes[2]; 
  int size = 0;

  if (kbd_subscribe_int(&bit_no) != 0) return 1;
  uint32_t irq_set = BIT(bit_no);

  while (kbd_get_scancode() != ESC_BREAKCODE) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            
            kbc_ih(); 

            if (kbd_has_error()) continue; 

            uint8_t current_scancode = kbd_get_scancode();
            
            bytes[size] = current_scancode;
            size++;

            if (current_scancode == TWO_BYTE_CODE) {
              continue; 
            }

            bool make = !(current_scancode & MAKECODE_BIT);

            kbd_print_scancode(make, size, bytes);
            
            size = 0; 
          }
          break;
        default:
          break;
      }
    }
  }

  // 3. Retira a subscrição das interrupções antes de sair
  if (kbd_unsubscribe_int() != 0) return 1;

  // 4. Imprime o número total de chamadas à função sys_inb
  kbd_print_no_sysinb(sys_inb_counter); 

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
