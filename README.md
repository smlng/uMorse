# uMorse
A (micro/u) Morse Encoder

# build

To build the test binary run

```
make -C tests/
./tests/test
```

The default delay for a Morse *DIT* is 60ms (milliseconds), which is quiet fast
for Morse beginners. To increase the timing interval, e.g. to 240ms, run

```
CFLAGS=-DUMORSE_DELAY_DIT=240 make -C tests/ clean all
./tests/test
```
