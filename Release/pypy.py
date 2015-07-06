import os
import subprocess

inp = open("input.txt", "w")
out = open("output2.txt", "w")

for x in range(201, 301):
    p = subprocess.Popen(['taskA10.exe'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    grep_stdout = p.communicate(input=bytes(str(x*1000)+'\n', 'UTF-8'))[0]
    o = grep_stdout.decode()
    out.write("({0}, {1})\n".format(str(x), o[0:len(o)-2]))