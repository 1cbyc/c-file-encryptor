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
5. oh, i forgot to make clear that i put the test file in `tests/test_input.txt` file, but then this is what i used in the text input:
```markdown
oya now, this is my test file. make we see if the encryption and decryption dey work well.
```
6. to those that are oversabinus like me, you can do some debugging sha. just add print statements to main.c file and then check the value of all arguments like the argc, the arg[1] and every other. 
```c
printf("argc: %d\n", argc);
for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
}
```

## my motivation
it is shit!