<img width="200" height="200" alt="KeepSpin" src="https://github.com/user-attachments/assets/72ae57ec-d1e5-46d0-9730-f01d2ce28b07" />

KeepSpin is a simple userspace program that keeps a DVD's spindle motor active to reduce stutter times
in aggressive spindle optimization firmware devices.

How does KeepSpin work?
It reads a random part of a block device. In this case /dev/sr0, requesting a read of a single byte periodically to reset any timers
for timeouts in DVD reading drive firmware. However this program isn't limited by block devices only, it can do other types of
block devices like /dev/sda1 and so on, alongside files.

How do i use KeepSpin?
At it's core:
./keepspinV1.2.x86_64 <block device> <seconds for a periodic random read>
It's simple to use, However you'll need to know your DVD driver's timeout, For that
there's the KeepSpin-calibrate program, which will make a random read and when the disc stops spinning
you'll press enter. Afterwards the program will give you a timeout, and you'll use that.

To compile the programs you do your regular:
gcc keepspin.c -o keepspin command on both .c files

If you don't have GCC, simply download the executables (the ones on /compiled-recent)

<img width="100" height="100" alt="uma-musume-agnes-tachyon" src="https://github.com/user-attachments/assets/45def0b5-f46c-44a0-afa3-43bf8f0dae0c" />
