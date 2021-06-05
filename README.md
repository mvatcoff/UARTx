# UARTX

	This is a software to write and read data from USB-UART port in Linux systems.
	Very useful to establish connections with embedded systems how to Arduino, ESP, Raspberry Pi, FPGA, etc.

# USAGE

```
uartx [Port] [Mode] [Speed bps] [Options]

		[Port]
			PATH of port
		[Mode]
			bit_data|parity|stop_bit
		[Speed bps]
			Port transmission speed in bps	 
		[Options]
			-t 	PATH of log file
```

# EXAMPLE

```
uartx /dev/ttyUSB0 8N1 9600

uartx /dev/ttyS0 8N1 9600

uartx /dev/ttyUSB0 8N1 9600 -t log.txt
```

# INSTALL

```
$ make

$ sudo make install

$ make clean
```
