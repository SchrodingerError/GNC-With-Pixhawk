uint64 timestamp                    # time since system start (microseconds)

uint16 num_registers = 128          # How many registers can be stored in register_array_read

uint16[128] register_array_read     # Array of unsigned, 16 bit registers that are read from the PLC