#include <iostream>
#include <string>

using namespace std;

class CaesarCipher{
    private:
        int shiftValue;
    protected:
        string encode(const string& message){
            string encodedMessage = "";
            for (int i = 0; i < message.length(); i++) {
                char chr = message[i];
                if (isalpha(chr)) {
                    char newCharacter = chr + shiftValue;

                    if (isupper(chr) && newCharacter > 'Z'){
                        newCharacter -= 26;
                    }else if(islower(chr) && newCharacter > 'z') {
                        newCharacter -= 26;
                    }
                    encodedMessage += newCharacter;
                } 
                else {
                    encodedMessage += chr;
                    }
            }
            return encodedMessage;
        }
    public:
        void setShiftValue(int value) {
            shiftValue = value;
        }
        string decode(const string& encodedMessage) {
            string decodedMessage = "";
            for (int i = 0; i < encodedMessage.length(); i++) {
                char chr = encodedMessage[i] ;
                if (isalpha(chr)) {
                    char newCharacter = chr - shiftValue;
                    // Handle wrap around from A to Z or a to z
                    if (isupper(chr) && newCharacter < 'A'){
                        newCharacter += 26;
                    }else if(islower(chr) && newCharacter < 'a') {
                        newCharacter += 26;
                    }
                    decodedMessage += newCharacter;
                }
                else{
                    decodedMessage += chr;
                }
            }
            return decodedMessage;
        }
        string encodeMessage(const std::string& message) {
            return encode(message);
        }
};

class Rot13Cipher : public CaesarCipher{
    public:
        Rot13Cipher(){
            setShiftValue(13);
        }
};

int main(){
    cout << "\tWelcome to this Cipher Decrypting program!" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << endl;
    bool notAlpha = false;
    int shiftValue = 7, guess;
    int chances = 4;
    char choice;
    string message, encodedMessage, decodedMessage, guessDecode;
    encodedMessage = "Mvvawypuaz";
    do{
        cout << "\nWould you like to encode a new message? ('Y/y' for yes or 'N/n' for no): ";
        cin >> choice;
        cout << endl;
        if(!((choice == 'y') || (choice == 'Y') || (choice == 'n') || (choice == 'N'))){
            cout << "Enter a valid option!" << endl;
            continue;
        }
    } while(!((choice == 'y') || (choice == 'Y') || (choice == 'n') || (choice == 'N')));
    if ((choice == 'y') || (choice == 'Y')){
        do{
            notAlpha = false;
            cout << "Enter the message you would like to encode: ";
            cin.ignore();
            getline(cin, message);
            if (message.empty() && cin.peek() == '\n'){
                cout << "You didn't enter any message! Please try again.\n" << endl;
                continue;
            }
            else if(!message.empty()){
                for (int i = 0; i < message.length(); i++){
                    if(!isalpha(message[i]) && message[i]!= ' '){
                        notAlpha = true;
                        break;
                    }
                }
                if (notAlpha == true){
                        cout << "Your message cannot have any non-alphabetic characters. Please try again!\n" << endl;
                }
            }
            if(message.length() > 0 && notAlpha == false){break;}
        } while(true);

        do {
            cout << "How many positions should each character be shifted? (1-13): ";
            cin >> shiftValue;
            if (!(shiftValue >= 1 && shiftValue <= 13)){
                cout << "\nInvalid input! Enter a number between 1 and 13." << endl;
            }
            else{break;}
        } while (true);
        CaesarCipher* cipher;
        if(shiftValue == 13){
            cipher = new Rot13Cipher;
            cipher -> setShiftValue(shiftValue);
            encodedMessage = cipher -> encodeMessage(message);
            delete cipher;
        }else{
            cipher = new CaesarCipher;
            cipher -> setShiftValue(shiftValue);
            encodedMessage = cipher -> encodeMessage(message);
            delete cipher;
        }
        system("clear");
        cout << "\nEncoded Message using Caesar Cipher (shift value " << shiftValue << "): " << encodedMessage << endl;
    do{
        cout << "\nWould you like to decode the message? ('Y/y' for yes or 'N/n' for no): ";
        cin >> choice;
        cout << endl;
        if(!((choice == 'y') || (choice == 'Y') || (choice == 'n') || (choice == 'N'))){
            cout << "Enter a valid option!" << endl;
            continue;
        }
    } while(!((choice == 'y') || (choice == 'Y') || (choice == 'n') || (choice == 'N')));
    if ((choice == 'y') || (choice == 'Y')){
        do{
            cout << "\nThe more you take, the more you leave behind. What is it called?" << endl;
            cout << "The encoded message: " << encodedMessage << endl;
            cout << "\nEnter the shift value (1-13) you would like to use to decode the message: ";
            cin >> guess;
            if (guess  < 1 || guess > 13) {
                cout << "\nInvalid value! Enter a number between 1 - 13." << endl;
            }
            else{
                if (guess != shiftValue){
                    chances--;
                    cout << "\nThat shift value is incorrect.\nYou have " << chances << " chances left!" << endl;
                }
                if (shiftValue == 13){
                    Rot13Cipher* cipher;
                    cipher = new Rot13Cipher;
                    decodedMessage = cipher -> decode(encodedMessage);
                    delete cipher;
                }
                else{
                    CaesarCipher* cipher = new CaesarCipher;
                    cipher -> setShiftValue(shiftValue);
                    decodedMessage = cipher -> decode(encodedMessage);
                    delete cipher;
                }
            }
            if (chances == 2){
                cout << "\nHint: I leave marks." << endl;
            }
            if (chances == 0){
                cout << "\nYou have ran out of tries! The correct shift value is " << shiftValue << "." << endl;
                cout << "\nThe encoded message was: " << decodedMessage << endl;
                break;
            }
            else if(guess == shiftValue){
                cout << "\nCongrats! You have successfully decoded the message.\n";
                cout << "\nThe decoded message is: " << decodedMessage << endl;
                break;
            }
        } while (true);    
    }
    cout << endl;
    cout << "Thank you for using this program!" << endl;
    cout << "Exiting..." <<  endl;
    return 0;
    }
}
