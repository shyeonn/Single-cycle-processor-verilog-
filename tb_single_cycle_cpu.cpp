#include <stdlib.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vsingle_cycle_cpu.h"

#define CLK_T 10
#define CLK_NUM 16
#define RST_OFF 2	// reset if released after this clock counts

int main(int argc, char** argv, char** env) {
	Vsingle_cycle_cpu *dut = new Vsingle_cycle_cpu;

	// initializing waveform file
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	dut->trace(m_trace, 5);
	m_trace->open("wave.vcd");

	FILE *fp = fopen("report.txt", "w");

	// test vector
	unsigned int cc = 0;	// clock count
	unsigned int tick = 0;	// half clock
	dut->clk = 1;
	dut->reset_b = 0;
	while (cc < CLK_NUM) {
		dut->clk ^= 1;
		if (cc==RST_OFF) dut->reset_b = 1;
		if (dut->clk==0) {
			printf("CC:%04d ", cc);
			printf("opcode :%04x ", dut->single_cycle_cpu__DOT__opcode);
 //			printf("inst :%04x ", dut->single_cycle_cpu__DOT__inst);
			printf("pc_curr :%04x ", dut->single_cycle_cpu__DOT__pc_curr);
//			printf("alu_op:%04x ", dut->single_cycle_cpu__DOT__alu_op);
			printf("alu_control:%04x ", dut->single_cycle_cpu__DOT__alu_control);
//			printf("imm12:%04x ", dut->single_cycle_cpu__DOT__imm12);
//			printf("in1:%04x ", dut->single_cycle_cpu__DOT__u_alu_0__DOT__in1);
//			printf("in2:%04x ", dut->single_cycle_cpu__DOT__u_alu_0__DOT__in2);
			printf("result@alu:%04x ", dut->single_cycle_cpu__DOT__u_alu_0__DOT__result);
//			printf("mem_to_reg :%04x ", dut->single_cycle_cpu__DOT__mem_to_reg);
//			printf("rd_din:%04x ", dut->single_cycle_cpu__DOT__rd_din);
			printf("alu_in1:%04x ", dut->single_cycle_cpu__DOT__alu_in1);
			printf("alu_in2:%04x ", dut->single_cycle_cpu__DOT__alu_in2);
			printf("alu_src:%04x ", dut->single_cycle_cpu__DOT__alu_src);
//			printf("reg_write:%04x ", dut->single_cycle_cpu__DOT__reg_write);
//			printf("rd:%04x ", dut->single_cycle_cpu__DOT__rd);
//			printf("mem_read:%04x ", dut->single_cycle_cpu__DOT__mem_read);
//			printf("mem_write:%04x ", dut->single_cycle_cpu__DOT__mem_write);
//			printf("pc_next :%04x ", dut->single_cycle_cpu__DOT__pc_next);
			printf("funct3:%04x ", dut->single_cycle_cpu__DOT__funct3);
			printf("pc_next_sel :%04x ", dut->single_cycle_cpu__DOT__pc_next_sel);
			printf("alu_op :%04x ", dut->single_cycle_cpu__DOT__alu_op);
			printf("branch: %04x ", dut->single_cycle_cpu__DOT__branch);
			printf("alu_zero:%04x ", dut->single_cycle_cpu__DOT__alu_zero);
			printf("\n");
			cc++;
		}
		dut->eval();
		m_trace->dump(tick*CLK_T/2);
		tick++;
	}

	dut->eval();
	m_trace->dump(tick);

	for (int i = 0; i < 32; i++) {
		fprintf(fp, "RF[%02d]: %016lx\n", i, dut->single_cycle_cpu__DOT__u_regfile_0__DOT__rf_data[i]);
	}
	for (int i = 0; i < 8; i++) {
		fprintf(fp, "DMEM[%02d]: %016lx\n", i, dut->single_cycle_cpu__DOT__u_dmem_0__DOT__data[i]);
	}

	fclose(fp);
	m_trace->close();
	delete dut;
	exit(EXIT_SUCCESS);
}
