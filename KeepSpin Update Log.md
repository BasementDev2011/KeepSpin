KeepSpin V1.0

Basic functionality and simple randomness to avoid caching.

KeepSpin V1.1

+ Added extra parameter for avoiding caching, random value sum, To avoid the PC from reading back
 the same data that was previously read and that is on cache.

KeepSpin V1.2

- Removed extra parameter where the user had to input a random amount of values
+ Using /dev/urandom for better (and more automatic) random reads on disc
