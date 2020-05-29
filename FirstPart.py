import hashlib

def hash_file_print(file_path):
    with open(file_path, 'rb') as f:
        hash_str = hashlib.md5()
        while True:
            data = f.read(8192)
            if not data:
                break
            hash_str.update(data)
    print(file_path + ": " + hash_str.hexdigest());

if __name__ == "__main__":
    file_path = input("Type file path: ")
    hash_file_print(file_path)
