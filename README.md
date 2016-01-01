# yeah
This is an improved version of the Unix 'yes' command. Some programs
never quit if the standard input continues to feed data. This program
adds the number of seconds to fire to limit how long this program will
continue in a loop. Also it has a firing rate option if that is desired.

## Usage
```
Usage: yeah [-r <rate>] [-s <duration>] [STRING]
  -r {seconds}  the firing rate in seconds. E.g. -r 0.5
  -s {seconds}  the number of seconds to fire. Default is infinity.
  -h            display this help and exit.
```
