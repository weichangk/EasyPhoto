import os

def get_files():
    for filepath,dirnames,filenames in os.walk(r'F:\weick\mycode\QtNote\imagemagickwrapper\magick\include\MagickCore'):
        for filename in filenames:
            print (filename)

get_files()
