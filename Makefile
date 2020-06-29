src=USBx.c
exe=usbx
cc=gcc -Wall
obj=obj/ctrl_argv.o obj/khbit_loop.o obj/setup_port.o

usbx: $(src) $(obj)
	$(cc) $(obj) $(src) -o $(exe)

obj/ctrl_argv.o: lib/ctrl_argv.c
	$(cc) -c lib/ctrl_argv.c -o obj/ctrl_argv.o

obj/khbit_loop.o: lib/khbit_loop.c
	$(cc) -c lib/khbit_loop.c -o obj/khbit_loop.o

obj/setup_port.o: lib/setup_port.c
	$(cc) -c lib/setup_port.c -o obj/setup_port.o

clean:
	rm obj/ctrl_argv.o obj/khbit_loop.o obj/setup_port.o
