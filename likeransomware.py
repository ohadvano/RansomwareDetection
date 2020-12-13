import random
import string
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random
import threading
import os
import sys
from os import walk

def EncryptFile(fileToEncrypt):
    print(fileToEncrypt)

def EncryptAllFiles(filesToEncrypt):
    for file_to_encrypt in filesToEncrypt:
        EncryptFile(file_to_encrypt)

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

###################### main ######################

base_path = "/home/ohadoz/Desktop/RansomwareDetection/TestData/output/TestFiles"
files_to_encrypt = GetAllFiles(base_path)
EncryptAllFiles(files_to_encrypt)