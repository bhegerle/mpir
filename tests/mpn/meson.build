tests = [
    't-addadd_n'
]

foreach test : tests
    exe = executable(test, test + '.c', 
        include_directories : test_inc,
        link_with : [mpir_lib, test_lib])
    test(test, exe)
endforeach
