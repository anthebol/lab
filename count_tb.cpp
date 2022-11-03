#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "../vbuddy.cpp"//"../" can use file located at upper level. e.g. vbuddy.cpp not under task 2 file,but can still use it with "../"

int main(int argc, char **argv, char **env)
{
    int i;
    int clk;

    Verilated ::commandArgs(argc, argv);

    Vcounter* top = new Vcounter;

    Verilated :: traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    //init Vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");


    top->clk = 1;
    top->rst = 1;
    top->en = 0;  
    
      

    for(i=0; i<300; i++)
    {
        for(clk=0;clk<2; clk++)
        {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();

        }
            vbdPlot(int(top->count), 0, 100);
        top->rst =(i<2) | (i==15);
        top->en = vbdFlag();
        if(Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();

    exit(0);
}
