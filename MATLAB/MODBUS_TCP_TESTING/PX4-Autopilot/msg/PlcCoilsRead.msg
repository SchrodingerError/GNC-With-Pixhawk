uint64 timestamp              # time since system start (microseconds)

uint16 num_coils = 128        # How many coils can be stored in coil_array

bool[128] coil_array_read     # Array of bools that are read from the PLC