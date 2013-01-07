/*
    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deviation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <libopencm3/stm32/f1/adc.h>
#include <libopencm3/stm32/f1/rcc.h>
#include <libopencm3/stm32/f1/dma.h>
#include "common.h"
#include "devo.h"
#include <stdlib.h>
#include <stdio.h>

static u16 ADC1_Read(u8 channel);
u16 adc_array_raw[NUM_ADC_CHANNELS];

void ADC_Init(void)
{
    int i;
    rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
    /* Make sure the ADC doesn't run during config. */
    adc_off(ADC1);


    rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);

    /* We configure to scan the entire group each time conversion is requested. */
    adc_enable_scan_mode(ADC1);
    adc_set_single_conversion_mode(ADC1);
    adc_disable_discontinuous_mode_regular(ADC1);
    adc_disable_external_trigger_regular(ADC1);
    adc_set_right_aligned(ADC1);

    /* We want to read the temperature sensor, so we have to enable it. */
    adc_enable_temperature_sensor(ADC1); 
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_28DOT5CYC);

    adc_power_on(ADC1);

    /* Wait for ADC starting up. */
    for (i = 0; i < 800000; i++)    /* Wait a bit. */
        __asm__("nop");

    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);

    //Build a RNG seed using ADC 14, 16, 17
    u32 seed = 0;
    for(int i = 0; i < 8; i++) {
        seed = seed << 4 | ((ADC1_Read(16) & 0x03) << 2) | (ADC1_Read(17) & 0x03); //Get 2bits of RNG from Temp and Vref
        seed ^= ADC1_Read(14) << i; //Get a couple more random bits from Voltage sensor
    }
    adc_disable_temperature_sensor(ADC1); 
    printf("RNG Seed: %08x\n", (int)seed);
    srand(seed);

    /* The following is based on code from here: http://code.google.com/p/rayaairbot */
    /* Enable DMA clock */
    rcc_peripheral_enable_clock(&RCC_AHBENR, RCC_AHBENR_DMA1EN);
    /* no reconfig for every ADC group conversion */
    dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
    /* the memory pointer has to be increased, and the peripheral not */
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    /* ADC_DR is only 16bit wide in this mode */
    dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
    /*destination memory is also 16 bit wide */
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
    /* direction is from ADC to memory */
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
    /* get the data from the ADC data register */
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1,(u32) &ADC_DR(ADC1));
    /* put everything in this array */
    dma_set_memory_address(DMA1, DMA_CHANNEL1, (u32) &adc_array_raw);
    /* we convert only 3 values in one adc-group */
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, NUM_ADC_CHANNELS);
    /* we want an interrupt after the adc is finished */
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);

    /* dma ready to go. waiting til the peripheral gives the first data */
    dma_enable_channel(DMA1, DMA_CHANNEL1);

    adc_enable_dma(ADC1);
    adc_set_regular_sequence(ADC1, NUM_ADC_CHANNELS, (u8 *)adc_chan_sel);
}

u16 ADC1_Read(u8 channel)
{
    u8 channel_array[1];
    /* Select the channel we want to convert. 16=temperature_sensor. */
    channel_array[0] = channel;
    adc_set_regular_sequence(ADC1, 1, channel_array);

    /*
     * If the ADC_CR2_ON bit is already set -> setting it another time
     * starts the conversion.
     */
    adc_start_conversion_direct(ADC1);

    /* Wait for end of conversion. */
    while (!(ADC_SR(ADC1) & ADC_SR_EOC));
    return(ADC_DR(ADC1));
}

void ADC_StartCapture()
{
    //while (!(ADC_SR(ADC1) & ADC_SR_EOC));
    adc_start_conversion_direct(ADC1);
}

void dma1_channel1_isr()
{
    medium_priority_cb();
    /* clear the interrupt flag */
    DMA_IFCR(DMA1) |= DMA_IFCR_CGIF1;

}
