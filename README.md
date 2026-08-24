<img width="698" height="698" alt="KeepSpin" src="https://github.com/user-attachments/assets/72ae57ec-d1e5-46d0-9730-f01d2ce28b07" />

KeepSpin is a simple userspace program that keeps a DVD's spindle motor active to reduce stutter times
in aggressive spindle optimization firmware devices.

This keeps the disc spinning indefinitely until you decide it shouldn't. By simply closing the program (Ctrl + C)

*How to use it?*

./keepspin /dev/sr0 25

/dev/sr0 being the block device
25 being the amount of seconds the program requests a read from the disc drive. (This is to prevent idle states in timeout)

*How do i know how many seconds i need to put for my DVD/CD Drive to not time out?*

Use the KeepSpin calibration program, in which you'll press ENTER until the spindle stops spinning.
./keepspin-calibrate /dev/sr0

All instructions are inside of the program.
