bool checkString(char* s) {
    int flag = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            flag = 1;
        }
        else if (s[i] == 'a' && flag == 1) {
            return false;
        }
    }

    return true;
}    
