import subprocess
import os
import ciff

def get_ciff(file):

    data, temp = os.pipe()
    os.write(temp, b"5 10\n")
    os.close(temp)

    # Compile
    subprocess.check_call([
        "g++", "Main.cpp", "ciff.cpp", "ciff_exception.cpp", "-o", "out"
    ])

    # Run
    s = subprocess.check_output(
        ["out", file],
        stdin=data
    )

    s = s.decode()
    s = s.split("\n")
    new_ciff = ciff.CIFF()
    if (s[0].startswith("Valid file")):
        new_ciff.is_valid = True
    else:
        new_ciff.is_valid = False
        new_ciff.error_message = s[0]

    return new_ciff