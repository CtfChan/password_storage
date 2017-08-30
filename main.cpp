#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int key = 5; 


string encrypt(string str, int k) {
    k%=26;
    int n = str.length();
    for (int i=0; i<n;i++) {
    	int charNum = str[i];
    	if (charNum >= 'a' && charNum <= 'z') { //handle lower case letters
    		charNum += k;
    		if (charNum > 'z') { //check if charNum is beyond ascii range for lowercase letters, lowercase a to z = 97 to 122
    			charNum = 96 + (charNum - 122);
    		}
    	} else if (charNum >= 'A' && charNum <= 'Z') { //handle upper case letters
    		charNum +=k;
    		if (charNum > 'Z') { // uppercase A to Z is 65 to 90
    			charNum = 64 + (charNum - 90);
    		}
    	}
    	str[i] = charNum;
    }
    return str;

}


string decrypt(string str, int k) {
	k%=26;
	int n = str.length();
	for (int i=0; i<n;i++) {
    	int charNum = str[i];
    	if (charNum >= 'a' && charNum <= 'z') { //handle lower case letters
    		charNum -= k;
    		if (charNum < 'a') {
    			charNum += k;
    			charNum = 123 - (k - (charNum - 97));
    		}

    	} else if (charNum >= 'A' && charNum <= 'Z') {
    		charNum -= k;
    		if (charNum < 'A') {
    			charNum += k;
    			charNum = 91 - (k - (charNum - 65));
    		}
    	}
    	str[i] = charNum;
   }
   return str;
}



int main() {
	int choice;

	while(1) {
		cout<<"\nChoose your choice ::";
		cout<<"\n1.) Add new account";
		cout<<"\n2.) Delete account";
		cout<<"\n3.) Modify account password";
		cout<<"\n4.) Display all acounts";
		cout<<"\n5.) Search for an account";
		cout<<"\n6.) Exit";
		cout<<"\nEnter your choice :: ";
		cin>>choice;

		switch (choice) {
			case 1: //ADD NEW ACCOUNT
			{
				ofstream outfile; 
				outfile.open("accounts.txt", ios::out | ios::app);
				cout<<"\n\nPlease Enter Details :: \n";
				
				cout<<"\nEnter the website :: ";
				string website;
				cin>>website;
                outfile<<website<<endl;
                
                cout<<"\nEnter username :: ";
                string username;
                cin>>username;
                outfile<<username<<endl;

                cout<<"\nEnter password ::";
                string pass;
                cin>>pass;
                pass = encrypt(pass, key);
                outfile<<pass<<endl;
				
				outfile.close();
			}
				break;

			case 2: //DELETE ACCOUNT
				{
					ofstream outfile;
					ifstream infile;
					outfile.open("temp.txt", ios::out);
					infile.open("accounts.txt", ios::in);

					string web, line;
					cout<<"\nEnter the website :: ";
					cin>>web;

					while(getline(infile, line)) {
						if (line == web) {
							getline(infile, line);
							getline(infile, line);
						}
						else {
							outfile<<line<<endl;
						}
					}
					outfile.close();
					infile.close();
				}
				remove("accounts.txt");
				rename("temp.txt", "accounts.txt");
				
				break;

			case 3:	//MODIFY PASSWORD
				{
					ofstream outfile;
					ifstream infile;
					outfile.open("temp.txt", ios::out); 
					infile.open("accounts.txt", ios::in);


					string web, newPass, line;
					cout<<"\nEnter the website :: ";
					cin>>web;
					cout<<"\nEnter the password :: ";
					cin>>newPass;
					newPass = encrypt(newPass, key);

					while(getline(infile, line)) {
						if (line == web) {
							outfile<<line<<endl;
							getline(infile, line);
							outfile<<line<<endl;
							getline(infile, line);
							outfile<<newPass<<endl;
						}
						else {
							outfile<<line<<endl;
						}
					}

					outfile.close();
					infile.close();

				}
				remove("accounts.txt");
				rename("temp.txt", "accounts.txt");

				break;

			case 4:	//DISPLAY ALL ACCOUNTS
				{
					ifstream infile;
					infile.open("accounts.txt", ios::in);
					string line;
					
					while(getline(infile, line)) {
						cout<<"\n\nWEBSITE: "<<line<<endl;
						getline(infile, line);
						cout<<"USERNAME: "<<line<<endl;
						getline(infile, line);
						line = decrypt(line, key);
						cout<<"PASSWORD: "<<line<<endl;
					}
					infile.close();
				}
				break;

			case 5: //SEARCH FOR AN ACCOUNT
				{
					string web;
					cout<<"\nEnter the website :: ";
					cin>>web;
					ifstream infile;
					infile.open("accounts.txt", ios::in);
					string line;
					bool found = false;
					while(getline(infile, line)) {
						if(line == web) {
							cout<<"Website found!"<<endl;
							cout<<"WEBSITE: "<<line<<endl;
							getline(infile, line);
							cout<<"USERNAME "<<line<<endl;
							getline(infile, line);
							line = decrypt(line, key);
							cout<<"PASSWORD "<<line<<endl;
							found = true;
							break;
						}
					}
					if (!found) {
						cout<<"\nWebsite not in directory"<<endl;
					}
				}
				

				break;

			case 6: // EXIT

				exit(0);

			default:
			{
				cout<<"\nInvalid choice. Please try again.\n";
			}
			exit(0);

		}

	}

}