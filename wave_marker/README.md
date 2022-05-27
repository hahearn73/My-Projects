Marks data chunk of wav files so that all bytes have a 1 at least significant bit.  
wave_marker.c can be be used to change the wav file in a way thats imperceptible to hearing, thus copyright marking it.  
mark_checker.c can be used to check if a file has been marked by wave_marker.c.  
Tested on 8 bit files, would work for 16 bit but would need a modification so that every other byte is marked rather than every byte.  

example usage (assuming wave_marker.c and mark_checker.c have been compiled to executables mark and check, respectively)  

$ ./mark example.wav > output.wav  
$ ./check output.wav  
marked  
$ ./check example.wav  
not marked  
