verilator -Wall --trace --cc --public single_cycle_cpu.sv imem.sv regfile.sv alu.sv dmem.sv --exe tb_single_cycle_cpu.cpp
make -C obj_dir -f Vsingle_cycle_cpu.mk Vsingle_cycle_cpu
./obj_dir/Vsingle_cycle_cpu
