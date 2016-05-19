{
    'targets': [
        {
            # To use this library add to dependencies at your .gyp file
            # 'dependencies' [
            #   './path/to/tweeno.gyp:tweeno'
            # ]
            'target_name': 'tweeno',

            # If you want to use it as a shared library change `type`
            # to 'shared_library' and add the following lines
            # 'cflags': [
            #   '-fPIC'
            # ],
            #
            'type': 'static_library',
            'ldflags': [
                '-std=c++11'
            ],

            # To use other easing functions add .cpp files here
            'sources': [
                    './Tweeno/src/Repeat.cpp',
                    './Tweeno/src/Tween.cpp',
                    './Tweeno/src/TweenList.cpp',
                    './Tweeno/src/Easing/Linear.cpp',
            ],
            'include_dirs': [
                './Tweeno/headers'
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    './Tweeno/headers'
                ]
            },
        }
    ]
}
