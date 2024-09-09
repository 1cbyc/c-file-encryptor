# file encryptor

## here me out! 
i am just testing a theory on mac, might even delete this. cause i have not actually used any of my macbooks to code C before this time. so i am trying out multiple things. it's always been on my pc.

## let me explain how you can use it sef
1. just run `make` to build the file (i have done all the work for you)
2. if you get issues, just use `make clean` and then `make` again to clean and rebuild
3. okay, back to the stuff i am explaining, after building, run the program for encryption:
```bash
./c-file-encryptor encrypt tests/test_input.txt tests/encrypted_output.txt secretkey
```
4. then, run for decryption if you like:
```bash
./c-file-encryptor decrypt tests/encrypted_output.txt tests/decrypted_output.txt secretkey
```
5. oh, i forgot