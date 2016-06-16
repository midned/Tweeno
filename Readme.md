# Tweeno - Tweening library for C++

Tweeno is a tweening library for C++*(11)* inspired by TweenLite

It includes Robert Penner's easing functions and it allows to use your own easing functions if wanted to.

## Usage

[The code is documented using Doxygen with a few examples](http://alv-c.github.io/Tweeno/html/).

## Installation

This library uses [GYP](https://gyp.gsrc.io).

Just add it to `dependencies` list inside your `.gyp` file

```python
'dependencies': [
  './path/to/Tweeno/tweeno.gyp:tweeno'
]
```

By default, only `Linear` easing is compiled. To use another easing functions you need to add its `.cpp` location at your `.gyp` file `sources`.

Example.

```python
# To use other easing functions add .cpp files here
'sources': [
        # (...) Your custom source files
        'path/to/Tweeno/Easing/Bounce.cpp',
		# And/or other easing functions like
		# Quad.cpp, Sine.cpp, etc.
],
```

## License

MIT License
