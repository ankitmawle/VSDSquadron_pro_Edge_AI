/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/cpu.h>
#include <metal/led.h>
#include <metal/button.h>
#include <metal/switch.h>
void processfclayer(int8_t *,  const uint32_t *, int32_t, uint32_t, uint32_t, int32_t *) __attribute__((section(".srodata"))) __attribute__((used));

#include "BitNetMCU_inference.h"
// #include "BitNetMCU_model_1k.h"
#include "BitNetMCU_model_12k.h"
const int8_t input_data_0[256] = {-22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 11.0, 64.0, 30.0, 6.0, -14.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 28.0, 124.0, 127.0, 115.0, 66.0, -3.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -12.0, 18.0, 58.0, 97.0, 124.0, 70.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -16.0, 47.0, 100.0, -11.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -21.0, 44.0, 104.0, -11.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -16.0, 68.0, 106.0, -12.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 99.0, -18.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -13.0, 77.0, 96.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -17.0, 62.0, 97.0, -20.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, 18.0, 71.0, -14.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -22.0, -20.0, -16.0, -21.0, -22.0, -22.0, -22.0, -22.0, -22.0};
const uint8_t label_0 = 7;
const int8_t input_data_1[256] = {-20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -4.0, 69.0, 6.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 5.0, 106.0, 42.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 28.0, 119.0, 50.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -14.0, 64.0, 125.0, 19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 3.0, 99.0, 121.0, 13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -19.0, 33.0, 120.0, 100.0, -7.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -16.0, 71.0, 126.0, 65.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 6.0, 106.0, 112.0, 13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 47.0, 125.0, 100.0, -3.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 54.0, 127.0, 68.0, -19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 53.0, 119.0, 43.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 16.0, 59.0, -3.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0};
const uint8_t label_1 = 1;
const int8_t input_data_2[256] = {-21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -16.0, 11.0, 49.0, 48.0, 0.0, -20.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -20.0, -5.0, 41.0, 80.0, 62.0, 56.0, 70.0, 0.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -18.0, 10.0, 76.0, 58.0, 3.0, -18.0, -14.0, 70.0, 24.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -19.0, 28.0, 94.0, 29.0, -15.0, -21.0, -21.0, 1.0, 99.0, 47.0, -20.0, -21.0, -21.0, -21.0, -21.0, -21.0, 7.0, 87.0, 29.0, -19.0, -21.0, -20.0, -9.0, 65.0, 90.0, 7.0, -21.0, -21.0, -21.0, -21.0, -21.0, -19.0, 55.0, 67.0, -14.0, -21.0, -20.0, -4.0, 77.0, 118.0, 30.0, -19.0, -21.0, -21.0, -21.0, -21.0, -21.0, -17.0, 68.0, 33.0, -12.0, -0.0, 29.0, 69.0, 127.0, 72.0, -12.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -18.0, 55.0, 91.0, 84.0, 75.0, 38.0, 51.0, 111.0, 8.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -11.0, 16.0, 14.0, -8.0, -13.0, 62.0, 65.0, -18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -3.0, 84.0, 18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, 14.0, 68.0, -13.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, 8.0, 39.0, -17.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -20.0, -18.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0, -21.0};
const uint8_t label_2 = 9;
const int8_t input_data_3[256] = {-20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -13.0, -15.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -6.0, 41.0, 78.0, 38.0, -18.0, -20.0, -20.0, -20.0, -20.0, -17.0, -17.0, -20.0, -20.0, -20.0, -20.0, -11.0, 67.0, 109.0, 63.0, 6.0, -20.0, -20.0, -20.0, -20.0, -8.0, 48.0, 50.0, -8.0, -20.0, -20.0, -20.0, 2.0, 108.0, 65.0, -14.0, -20.0, -20.0, -20.0, -20.0, -12.0, 59.0, 114.0, 89.0, 4.0, -20.0, -20.0, -20.0, 10.0, 114.0, 27.0, -20.0, -20.0, -20.0, -20.0, -20.0, 36.0, 122.0, 65.0, -14.0, -20.0, -20.0, -20.0, -20.0, -2.0, 96.0, 55.0, -13.0, -20.0, -20.0, -20.0, -12.0, 89.0, 114.0, 16.0, -20.0, -20.0, -20.0, -20.0, -20.0, -17.0, 43.0, 100.0, 46.0, -5.0, -15.0, -18.0, 6.0, 115.0, 84.0, -9.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -14.0, 45.0, 115.0, 100.0, 78.0, 50.0, 66.0, 127.0, 53.0, -17.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -13.0, 28.0, 76.0, 91.0, 104.0, 127.0, 122.0, 28.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -19.0, -16.0, -14.0, -1.0, 71.0, 114.0, 8.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, 19.0, 112.0, 39.0, -13.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -11.0, 70.0, 89.0, 19.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -18.0, -6.0, -18.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0, -20.0};
const uint8_t label_3 = 4;

#define RTC_FREQ    32768

struct metal_cpu *cpu;
struct metal_interrupt *cpu_intr, *tmr_intr;
int tmr_id;
volatile uint32_t timer_isr_flag;

void BitMnistInference(const int8_t *input, const uint8_t label, const uint8_t sample) {
    int32_t layer_out[MAX_N_ACTIVATIONS];
    int8_t layer_in[MAX_N_ACTIVATIONS];
	int32_t prediction;
	uint32_t startticks, endticks;

//	startticks = SysTick->CNT;
    processfclayer((int8_t*)input, L1_weights, L1_bitperweight, L1_incoming_weights, L1_outgoing_weights, layer_out);
    ReLUNorm(layer_out, layer_in, L1_outgoing_weights);

    processfclayer(layer_in, L2_weights, L2_bitperweight, L2_incoming_weights,  L2_outgoing_weights, layer_out);
    ReLUNorm(layer_out, layer_in, L2_outgoing_weights);

    processfclayer(layer_in, L3_weights, L3_bitperweight, L3_incoming_weights,  L3_outgoing_weights, layer_out);
    prediction=ReLUNorm(layer_out, layer_in, L3_outgoing_weights);

#if NUM_LAYERS == 4
    processfclayer(layer_in, L4_weights, L4_bitperweight, L4_incoming_weights,  L4_outgoing_weights, layer_out);
    prediction=ReLUNorm(layer_out, layer_in, L4_outgoing_weights);
#endif

//	endticks = SysTick->CNT;

	printf( "Inference of Sample %d\tPrediction: %ld\tLabel: %d\t\n", sample, prediction, label);
}


void display_banner (void) {

    printf("\n");
    printf("\n");
    printf("                  SIFIVE, INC.\n");
    printf("\n");
    printf("           5555555555555555555555555\n");
    printf("          5555                   5555\n");
    printf("         5555                     5555\n");
    printf("        5555                       5555\n");
    printf("       5555       5555555555555555555555\n");
    printf("      5555       555555555555555555555555\n");
    printf("     5555                             5555\n");
    printf("    5555                               5555\n");
    printf("   5555                                 5555\n");
    printf("  5555555555555555555555555555          55555\n");
    printf("   55555           555555555           55555\n");
    printf("     55555           55555           55555\n");
    printf("       55555           5           55555\n");
    printf("         55555                   55555\n");
    printf("           55555               55555\n");
    printf("             55555           55555\n");
    printf("               55555       55555\n");
    printf("                 55555   55555\n");
    printf("                   555555555\n");
    printf("                     55555\n");
    printf("                       5\n");
    printf("\n");

    printf("\n");
    printf("               Welcome to SiFive!\n");

}

void timer_isr (int id, void *data) {

    // Disable Timer interrupt
    metal_interrupt_disable(tmr_intr, tmr_id);

    // Flag showing we hit timer isr
    timer_isr_flag = 1;
}

void wait_for_timer(struct metal_led *which_led) {

    // clear global timer isr flag
    timer_isr_flag = 0;

    // Turn on desired LED
    metal_led_on(which_led);

    // Set timer
    metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + RTC_FREQ);

    // Enable Timer interrupt
    metal_interrupt_enable(tmr_intr, tmr_id);

    // wait till timer triggers and isr is hit
    while (timer_isr_flag == 0){};

    timer_isr_flag = 0;

    // Turn off this LED
    metal_led_off(which_led);
}

int main (void)
{
    int rc;
    struct metal_led *led0_red, *led0_green, *led0_blue;

    // This demo will toggle LEDs colors so we define them here
    led0_red = metal_led_get_rgb("LD0", "red");
    led0_green = metal_led_get_rgb("LD0", "green");
    led0_blue = metal_led_get_rgb("LD0", "blue");
    if ((led0_red == NULL) || (led0_green == NULL) || (led0_blue == NULL)) {
        printf("At least one of LEDs is null.\n");
        return 1;
    }

    // Enable each LED
    metal_led_enable(led0_red);
    metal_led_enable(led0_green);
    metal_led_enable(led0_blue);

    // All Off
    metal_led_off(led0_red);
    metal_led_off(led0_green);
    metal_led_off(led0_blue);

    // Lets get the CPU and its interrupt
    cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    if (cpu == NULL) {
        printf("CPU null.\n");
        return 2;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu);
    if (cpu_intr == NULL) {
        printf("CPU interrupt controller is null.\n");
        return 3;
    }
    metal_interrupt_init(cpu_intr);

    // display welcome banner
    display_banner();

	printf("Starting MNIST inference...\n");
	BitMnistInference(input_data_0, label_0,1);
	BitMnistInference(input_data_1, label_1,2);
	BitMnistInference(input_data_2, label_2,3);
	BitMnistInference(input_data_3, label_3,4);

    // Setup Timer and its interrupt so we can toggle LEDs on 1s cadence
    tmr_intr = metal_cpu_timer_interrupt_controller(cpu);
    if (tmr_intr == NULL) {
        printf("TIMER interrupt controller is  null.\n");
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_isr, cpu);
    if (rc < 0) {
        printf("TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Lastly CPU interrupt
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        printf("CPU interrupt enable failed\n");
        return 6;
    }

    // Red -> Green -> Blue, repeat
    while (1) {

        // Turn on RED
        wait_for_timer(led0_red);

        // Turn on Green
        wait_for_timer(led0_green);

        // Turn on Blue
        wait_for_timer(led0_blue);

    }

    // return
    return 0;
}
