import subprocess

zero = 0

for x in range (10000000):
        x = subprocess.check_output(['./bonus3', str(zero)])

        if len(x) > 1:
                print(len(x))
        zero -= 1
        print(zero)