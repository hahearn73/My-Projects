Marks data chunk of wav files so that all bytes have a 1 at least significant bit.
wave_marker.c an be be used to change the wav file in a way thats imperceptible to hearing, thus copyright marking it.
Tested on 8 bit files, would work for 16 bit but would need a small modification so that every other byte is marked rather than every byte.
