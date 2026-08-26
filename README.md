<img width="200" height="200" alt="KeepSpin" src="https://github.com/user-attachments/assets/72ae57ec-d1e5-46d0-9730-f01d2ce28b07" />

KeepSpin is a simple userspace program that keeps a DVD's spindle motor active to reduce stutter times
in aggressive spindle optimization firmware devices.

This keeps the disc spinning indefinitely until you decide it shouldn't. By simply closing the program (Ctrl + C)

*How to use it?*

./keepspin /dev/sr0 25 1337

/dev/sr0 being the block device
25 being the amount of seconds the program requests a read from the disc drive. (This is to prevent idle states in timeout)
1337 is the random state. This is to prevent the disc from trying to predict the reading position
Make sure to always place a different random state when using keepspin. Otherwise the bytes that were read and (likely cached)
Will be simply read back from the cache, thus defeating the entire purpose of making the spindle continue operations, Since
The byte was grabbed from the cache, and not the disc drive.

*How do i know how many seconds i need to put for my DVD/CD Drive to not time out?*

Use the KeepSpin calibration program, in which you'll press ENTER until the spindle stops spinning.
./keepspin-calibrate /dev/sr0

All instructions are inside of the program.

To compile them you do your regular:
gcc keepspin.c -o keepspin command on both .c files

If you don't have GCC, simply download the executables (the ones on /compiled)

I hope that what i made was useful.
<img width="100" height="100" alt="uma-musume-agnes-tachyon" src="https://github.com/user-attachments/assets/45def0b5-f46c-44a0-afa3-43bf8f0dae0c" />
