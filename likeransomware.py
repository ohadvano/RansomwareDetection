import random
import string
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random
import threading
import os
import sys
from os import walk

encryption_timeout = 10
encrypted_symbol = "enc_"

def EncryptFile(fileToEncrypt, key):
    print(fileToEncrypt)
    #print(key)
    pass

def EncryptAllFiles(filesToEncrypt, key):
    for file_to_encrypt in filesToEncrypt:
        EncryptFile(file_to_encrypt, key)

def GetAllFiles(dirName):
    ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
    listOfFile = os.listdir(dirName)
    allFiles = list()
    for entry in listOfFile:
        fullPath = os.path.join(dirName, entry)
        if os.path.isdir(fullPath):
            allFiles = allFiles + GetAllFiles(fullPath)
        else:
            if fullPath.endswith(ext):
                allFiles.append(fullPath)
    return allFiles

def FuckTheSystem():
    base_path = "/home/ohadoz/Desktop/RansomwareDetection/TestData/output/TestFiles"
    files_to_encrypt = GetAllFiles(base_path)
    password = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32))
    key = SHA256.new(password.encode('utf-8')).digest()
    EncryptAllFiles(files_to_encrypt, key)

###################### main ######################

t1 = threading.Thread(target=FuckTheSystem)  # daemon thread runs the encrypt_all_files() function in background
t1.daemon = True  # make the thread run in bg
t1.start()  # start the encrypting thread
t1.join(encryption_timeout)

# If thread is still active
if t1.is_alive():
    print("terminated")
    t1.terminate()
    t1.join()
