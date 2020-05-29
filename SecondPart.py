import os
import threading
from FirstPart import hash_file_print

if __name__ == "__main__":
    dir_path = input("Type directory path: ")
    files_arr = os.listdir(dir_path)    # Files in direcrory
    threads_list = []                   # Thread list

    j = 0

    for file_name in files_arr:
        threads_list.insert(j, threading.Thread(target=hash_file_print, args=(dir_path+'/'+file_name,)))    # Insert new process in list
        threads_list[j].start()        # Start new thread
        j += 1

    for i in range(j):
        threads_list[i].join()         # Wait for all child threads
