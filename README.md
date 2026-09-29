# Overview
This project enables AXI GPIO to switches, leds, and an rgb led.
The hardware is exported from vivado and the software is programmed in Vitis.
With the GPIO accessible from the PS side we can control it with software, the 
program reads the switch states and displays diffrent led patterns and diffrent colors.

# Components Used:

*Zybo Z7 ARM/FPGA SoC Board

# Known Issues or Limitations:


# References

1. [Zybo Z7 Product Page](https://digilent.com/shop/zybo-z7-zynq-7000-arm-fpga-soc-development-board)
2. [Zybo Z7 Reference Manual](https://digilent.com/reference/programmable-logic/zybo-z7/reference-manual)
3. FTDI Windows ARM64 Driver
   - [FTDI Community Driver Link](https://www.ftdicommunity.com/index.php?topic=753.0)
   - [Digilent Forum Thread](https://forum.digilent.com/topic/22740-is-there-a-digilent-cable-driver-for-win11-on-arm/)
4. [AXI GPIO IP Documentation](https://docs.amd.com/r/en-US/pg144-axi-gpio/)