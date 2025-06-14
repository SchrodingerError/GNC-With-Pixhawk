uint64 timestamp              # time since system start (microseconds)

uint16 num_coils = 128        # How many coils can be stored in coil_array

bool[128] coil_array_write    # Array of bools that are used for writing to the PLC

bool written                  # Has the coil_array_write been written yet to the PLC