#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

string substitution(string s, string argv){
    for(int i=0, n = strlen(s); i<n; i++){
        if(islower(s[i])){
            s[i] = toupper(s[i]);
                int index = s[i] - 'A';
                s[i] = argv[index];
            s[i] = tolower(s[i]);
        } else if(isupper(s[i])){
            int index = s[i] - 'A';
            s[i] = argv[index];
        } else {
            //nothing
        }
    }
    return s;
}

int main(int argc, string argv[]){

    if(argc != 2)
    {
        printf("Arg given should be exactly one\n");
        return 1;
    }

    for(int i=0, n=strlen(argv[1]); i<n; i++){
        if(!isalpha(argv[1][i]) || (n != 26) || !isupper(argv[1][i])){
            printf("The arg should include just letters, uppercase, exactly 26 and have to be differently!\n");
            return 1;
        }

        int count = 0;
        for(int j=0; j<n;j++){
            if(argv[1][i] == argv[1][j])
            {
                count++;
                if(count > 1){
                    printf("The arg should include just letters, uppercase, exactly 26 and have to be differently!\n");
                    return 1;
                }
            }
        }
    }

    string s = get_string("plaintext:");
    string c = substitution(s, argv[1]);
    printf("ciphertext:%s\n", c);
    return 0;
}
