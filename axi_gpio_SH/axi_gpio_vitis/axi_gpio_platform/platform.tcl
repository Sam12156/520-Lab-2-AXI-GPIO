# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\pog12\Documents\Vivado\axi_gpio_SH\axi_gpio_vitis\axi_gpio_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\pog12\Documents\Vivado\axi_gpio_SH\axi_gpio_vitis\axi_gpio_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {axi_gpio_platform}\
-hw {C:\Users\pog12\Documents\Vivado\axi_gpio_SH\axi_gpio_SH_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/pog12/Documents/Vivado/axi_gpio_SH/axi_gpio_vitis}

platform write
platform generate -domains 
platform active {axi_gpio_platform}
platform generate
