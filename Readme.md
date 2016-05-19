# Tweeno - Simple C++11 tweening library

Tweeno is a simple tweening library for C++11. It's inspired by TweenLite (in a future may be added a TimeLine-like feature to it)

It includes Robert Penner's easing functions and allows to use custom easing functions if wanted.

## Usage

[The code is documented using Doxygen with a few examples](http://alv-c.github.io/Tweeno/html/).

## Installation

This library now uses GYP so its easier for you to add it to your existing project

Just add the following lines to your `.gyp` file

```json
'dependencies' [
  './path/to/tweeno.gyp:tweeno'
]
```

To use other easing functions add the location of the `.cpp` file in `tweeno.gyp` file

Those instructions are already explained as comments at `tweeno.gyp`

## License

MIT License
