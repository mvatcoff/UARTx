src=USBx.c
exe=usbx
cc=gcc -Wall
obj=ctrl_argv.o khbit_loop.o setup_port.o

usbx: $(src) $(obj)
	$(cc) $(src) -o $(exe)

ctrl_argv.o: lib/ctrl_argv.c
	$(cc) -c lib/ctrl_argv.c

khbit_loop.o: lib/khbit_loop.c
	$(cc) -c lib/khbit_loop.c

setup_port.o: lib/setup_port.c
	$(cc) -c lib/setup_port.c

clean:
	rm ctrl_argv.o khbit_loop.o setup_port.o
