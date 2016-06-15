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
            'cflags': [
                '-std=c++11'
            ],

            # To use other easing functions add .cpp files here
            'sources': [
                    './Tweeno/Tween.cpp',
                    './Tweeno/TweenList.cpp',
                    './Tweeno/Easing/Linear.cpp',
            ],
            'include_dirs': [
                './'
            ],

            # Export include directory to targets depending on tweeno
            'direct_dependent_settings': {
                'include_dirs': [
                    './'
                ]
            }
        }
    ]
}
