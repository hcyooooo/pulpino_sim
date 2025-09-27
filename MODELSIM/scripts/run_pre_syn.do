# In Modelsim type: do run.do
# Create work library
vlib work

# Add Sources
do ../scripts/ips_src_files.do
do ../scripts/src_files.do

vlog -sv +define+SYNTHESIS {*}$SRC_AXI_NODE
vlog -sv +define+SYNTHESIS {*}$SRC_APB_NODE
vlog -sv +define+SYNTHESIS {*}$SRC_AXI_MEM_IF_DP
vlog -sv +define+SYNTHESIS {*}$SRC_AXI_SPI_SLAVE
vlog -sv +define+SYNTHESIS {*}$SRC_AXI_SPI_MASTER
vlog -sv +define+SYNTHESIS {*}$SRC_APB_UART_SV
vlog -sv +define+SYNTHESIS {*}$SRC_APB_GPIO
vlog -sv +define+SYNTHESIS {*}$SRC_APB_EVENT_UNIT {*}+incdir+../../RTL/ips/apb/apb_event_unit/include
vlog -sv +define+SYNTHESIS {*}$SRC_APB_SPI_MASTER
vlog -sv +define+SYNTHESIS {*}$SRC_APB_PULPINO
vlog -sv +define+SYNTHESIS {*}$SRC_APB_FLL_IF 
vlog -sv +define+SYNTHESIS {*}$SRC_CORE2AXI
vlog -sv +define+SYNTHESIS {*}$SRC_APB_TIMER
vlog -sv +define+SYNTHESIS {*}$SRC_AXI2APB
vlog -sv +define+SYNTHESIS {*}$SRC_APB_I2C
vlog -sv +define+SYNTHESIS {*}$SRC_AXI_SLICE_DC
vlog -sv +define+SYNTHESIS {*}$SRC_RISCV {*}+incdir+../../RTL/ips/riscv/include/
vlog -sv +define+SYNTHESIS {*}$SRC_RISCV_REGFILE_FPGA
vcom {*}$SRC_APB_UART
vlog -sv +define+SYNTHESIS {*}$SRC_AXI_SLICE
vlog -sv +define+SYNTHESIS {*}$SRC_ADV_DBG_IF
vlog -sv +define+SYNTHESIS {*}$SRC_APB2PER


# Add PULPino Files
vlog -sv +define+SYNTHESIS {*}$SRC_COMPONENTS
vlog -sv +define+SYNTHESIS {*}$SRC_PULPINO {*}+incdir+../../RTL/rtl/includes/


# Load Testbench
vlog -sv +define+SYNTHESIS ../../RTL/tb/tb.sv {*}+incdir+../../RTL/rtl/includes
vlog -sv +define+SYNTHESIS ../../RTL/tb/if_spi_master.sv
vlog -sv +define+SYNTHESIS ../../RTL/tb/if_spi_slave.sv
vlog -sv +define+SYNTHESIS ../../RTL/tb/uart.sv
vlog -sv +define+SYNTHESIS -timescale "1 ns / 1 ns" ../../RTL/tb/i2c_eeprom_model.sv


# Run Simultaion
#vsim -novopt -t ps tb

vsim -vopt -t ns work.tb -voptargs=+acc


# Add Traces to Waveform Window
add wave -position insertpoint  \
sim:/tb/top_i/clk \
sim:/tb/top_i/rst_n \
sim:/tb/top_i/fetch_enable_i \
sim:/tb/top_i/spi_clk_i \
sim:/tb/top_i/spi_cs_i \
sim:/tb/top_i/spi_sdi0_i \
sim:/tb/top_i/spi_sdi1_i \
sim:/tb/top_i/spi_sdi2_i \
sim:/tb/top_i/spi_sdi3_i \
sim:/tb/top_i/gpio_in \
sim:/tb/top_i/gpio_out \
sim:/tb/top_i/gpio_dir \
sim:/tb/top_i/core_region_i/CORE/RISCV_CORE/id_stage_i/registers_i/mem \
sim:/tb/top_i/core_region_i/CORE/RISCV_CORE/id_stage_i/registers_i/mem_fp \
sim:/tb/top_i/core_region_i/data_mem/sp_ram_i/mem


# Execution Time (depends on scheme)
run 20ns
