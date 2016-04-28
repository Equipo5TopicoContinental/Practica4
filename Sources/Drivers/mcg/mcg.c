/*
 * File:    mcg.c
 *
 * MCG drivers for Freescale Kinetis L - series devices
 * Notes:
 * Assumes the MCG mode is in the default FEI mode out of reset
 */

#include "mcg.h"
#include "derivative.h"

// global variables
extern int core_clk_khz;


char drs_val, dmx32_val;

/*********************************************************************************************/
/* Functon name : pll_init
 *
 * Mode transition: Option to move from FEI to PEE mode or to just initialize the PLL
 *
 * This function initializess PLL0. Either OSC0 is selected for the
 * reference clock source. The oscillators can be configured to use a crystal or take in an
 * external square wave clock.
 * Using the function parameter names the PLL frequency is calculated as follows:
 * PLL freq = ((crystal_val / prdiv_val) * vdiv_val)
 * Refer to the readme file in the mcg driver directory for examples of pll_init configurations.
 * All parameters must be provided, for example crystal_val must be provided even if the
 * oscillator associated with that parameter is already initialized.
 * The various passed parameters are checked to ensure they are within the allowed range. If any
 * of these checks fail the driver will exit and return a fail/error code. An error code will
 * also be returned if any error occurs during the PLL initialization sequence. Refer to the
 * readme file in the mcg driver directory for a list of all these codes.
 *
 * Parameters: crystal_val - external clock frequency in Hz either from a crystal or square
 *                           wave clock source
 *             hgo_val     - selects whether low power or high gain mode is selected
 *                           for the crystal oscillator. This has no meaning if an
 *                           external clock is used.
 *             erefs_val   - selects external clock (=0) or crystal osc (=1)
 *             prdiv_val   - value to divide the external clock source by to create the desired
 *                           PLL reference clock frequency
 *             vdiv_val    - value to multiply the PLL reference clock frequency by
 *             mcgout_select  - 0 if the PLL is just to be enabled, non-zero if the PLL is used
 *                              to provide the MCGOUT clock for the system.
 *
 * Return value : PLL frequency (Hz) or error code
 */
