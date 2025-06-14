uint64 timestamp                    # time since system start (microseconds)

uint16 num_registers = 128          # How many registers can be stored in register_array_write

uint16[128] register_array_write    # Array of unsigned, 16 bit registers that are used for writing to the PLC

bool written                        # Has the register_array_write been written yet to the PLC