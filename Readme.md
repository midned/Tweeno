# Tweeno - Simple C++11 tweening library

Tweeno is a simple tweening library for C++11. It's inspired by TweenLite (in a future may be added a TimeLine-like feature to it)

It includes Robert Penner's easing functions and allows to use custom easing functions if wanted.

## Documentation

[The code is documented using Doxygen](http://alv-c.github.io/Tweeno/html/), in a near future it may be added some examples besides the API documentation page (like usage within SDL2)

## Instalaltion

It has to be compiled within the program you are writing.

The `Tweeno/headers` folder must be added to the default includes `-iTweeno/headers` and all `.cpp` files inside `Tweeno/src` must be compiled.

All `.cpp` files inside `Tweeno/src/Easing` can be compiled but it will take some unnecessary extra time so you can specify to compile only the ones you are using. If you only use `Tweeno::Easing::Bounce` easing then you need only to compile `Tweeno/src/Easing/Bounce.cpp` file

## License

MIT License


