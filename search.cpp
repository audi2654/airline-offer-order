//One class, 3 funtions - AS, OP, OC

//1. Searching for market - AS
//2. Offer generation & pricing - OF
//3. PNR Creation - OC
    //PNR requires 5 mandatory elements to create a reservation/booking - PRINT
    //1. Phone number
    //2. Reservation Office / Received from
    //3. Itinerary
    //4. Name of pax
    //5. Ticket issuance status/time
    //once PNR generated I should be able to modify any of above 5 elements independently  

//4. Ticket Issuance - OC

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::endl;

#define NEWLINE std::cout << endl;
#define SPACE << " "

class bookAndTicket{
    public:
        //class local variables
        //PRINT elements
        std::string sPhoneNumber;
        std::string sReservationPCC;
        std::string sItinerary;
        std::string sName;
        bool bTicketingStatus;

        std::string sTravelDate;
        std::string sSelectedOffer;
        std::string sEmail;
        char cGender = 'N';
        std::string sDateOfBirth;

        //creating a no arg constructor & initializing vars to some default values
        bookAndTicket(){
            sPhoneNumber = "9876543210";
            sReservationPCC = "FLX1";
            sItinerary = "DXB-PNQ";
            sName = "Aditya";
            bTicketingStatus = false;
        }

        //function declarations/prototype
        void enterDetails();
        void ampAirShopping();
        void ampOfferPrice();
        void ampOrderCreate();
};

int main(){
    int a = {199+1};

    std::cout << a SPACE << "OK" << endl; NEWLINE

    bookAndTicket pnr1;
    pnr1.ampAirShopping();
    //pnr1.ampOfferPrice();
    //pnr1.ampOrderCreate();

    return 0;
}

//function definitions
void bookAndTicket::enterDetails(){
    //local vars

    //code
    std::cin.ignore();

    std::cout << "Enter Name : ";
    std::getline(std::cin, sName);
    std::cout << sName << endl; NEWLINE

    std::cout << "Enter Phone Number : ";
    std::getline(std::cin, sPhoneNumber);
    std::cout << sPhoneNumber << endl; NEWLINE

    std::cout << "Enter Email ID : ";
    std::getline(std::cin, sEmail);
    std::cout << sEmail << endl; NEWLINE

    std::cout << "Enter Date Of Birth (DD-MM-YYYY) : ";
    std::getline(std::cin, sDateOfBirth);
    std::cout << sDateOfBirth << endl; NEWLINE

    std::cout << "Enter Gender (F/M) : ";
    std::cin >> cGender;
    std::cout << cGender << endl; NEWLINE

}

void bookAndTicket::ampAirShopping()
{
    //local variable
    std::string sTempString, sTempString2;
    std::vector<std::string> sTempVec;
    bool bAvailabilityFlag = false;

    //code
    NEWLINE
    std::cout << "Enter travel date (DD-MM-YYYY) : ";
    std::cin >> sTravelDate; NEWLINE

    std::cout << "Enter 1 way route in given format XXX-XXX : ";
    //std::getline(std::cin, sItinerary);
    std::cin >> sItinerary; NEWLINE

    std::cout << "--------------AIRSHOPPING RS--------------"; NEWLINE

    //open file of markets
    //std::ifstream inputFile("markets.txt", std::ios::in);           //opening file with read mode
    std::ifstream inputFile("markets.txt");                           //opening file with read mode
    //inputFile.open("markets.txt");

        //print that tempStr
        //while(std::getline(inputFile, sTempString))                 //for some reason prints first character from file as whitespace               
        while(inputFile >> sTempString)                               //works perfectly without any space issue in .txt file
        {
            //std::cout << sTempString SPACE << "\n";
            sTempVec.push_back(sTempString);
        }
        
        /*for(auto i : sTempVec){
                std::cout << i; NEWLINE
        }*/

        //std::cout << sTempVec.at(5); NEWLINE    

        //compare it with itinerary string
        /*if(sItinerary.compare(sTempString) == 0){
            std::cout << "String Match" << endl; NEWLINE
        }
        else{
            std::cout << "String Do Not Match" << endl; NEWLINE
            std::cout << "sItinerary  : " << sItinerary << endl; NEWLINE
            std::cout << "sTempString : " << sTempString << endl; NEWLINE
        }*/

        //compare it with itinerary string
        for(auto i : sTempVec){
            if(sItinerary.compare(i) == 0){
                bAvailabilityFlag = true;
                sTempString2 = std::string(i);
                break;
            }
            else{
                bAvailabilityFlag = false;
            }
        }

        if(bAvailabilityFlag == true){
            std::cout << "Below Offers Available for Route : " << sTempString2  << " for Date " << sTravelDate << endl; NEWLINE
            ampOfferPrice();
        }
        else{
            std::cout << "No Fares Available for Route. Try from below list." << endl; NEWLINE
            for(auto i : sTempVec){
                std::cout << i; NEWLINE
            }
        }

        /*for(auto i = 0; i < sTempVec.size(); i++){
            //int itemp = sItinerary.compare(i);
            if(sItinerary == sTempVec.at(i)){
                std::cout << "String Match " << i << endl; NEWLINE
                break;
            }
        }*/

        // std::cout << "sItinerary  : " << sItinerary << endl; NEWLINE
        // std::cout << "sTempString : " << sTempString << endl; NEWLINE

    inputFile.close();
}

void bookAndTicket::ampOfferPrice(){
    //next step is to show 4 offers for sItinerary route
    //show as economy, premium economy, business & first class with Fares from prices.txt file
    //price them right in this RQ function & show final price to pay of pax with taxes
    //https://java2blog.com/split-string-space-cpp/

    //local vars
    std::ifstream inputFile;
    std::string sTempString, sTempString2;
    std::vector<std::string> sTempVec;
    unsigned int iClassOption = 0;
    char cCharOption = 'N';
    int num = 0;

    //code
    std::cout << "--------------OFFERPRICE RS--------------"; NEWLINE

    inputFile.open("classPrices.txt");

    //reading prices file & pushing its strings into sTempString
    while(inputFile >> sTempString)                               //works perfectly without any space issue in .txt file
    {
        //std::cout << sTempString SPACE << "\n";
        sTempVec.push_back(sTempString);
    }

    inputFile.close();

    for(auto i : sTempVec){
        std::cout << ++num << ". " << i; 
        NEWLINE
    }
    NEWLINE

    std::cout << "Enter preferred option : ";
    std::cin >> iClassOption;

    NEWLINE
    switch(iClassOption)
    {
        case 1:
        std::cout << "Accepted Offer is " << sTempVec.at(0); NEWLINE
        sSelectedOffer = sTempVec.at(0);
        break;

        case 2:
        std::cout << "Accepted Offer is " << sTempVec.at(1); NEWLINE
        sSelectedOffer = sTempVec.at(1);
        break;

        case 3:
        std::cout << "Accepted Offer is " << sTempVec.at(2); NEWLINE
        sSelectedOffer = sTempVec.at(2);
        break;

        case 4:
        std::cout << "Accepted Offer is " << sTempVec.at(3); NEWLINE
        sSelectedOffer = sTempVec.at(3);
        break;
    }

    do
        {
            NEWLINE
            std::cout << "Continue to Book & Issue Ticket (Y/N) ? : "; NEWLINE
            std::cin >> cCharOption;

            if(cCharOption == 'Y' || cCharOption == 'y'){
                std::cout << "\n ---Creating PNR & Issuing Ticket---";
                ampOrderCreate();
                return;
            }
        }
        while (cCharOption != 'N' || cCharOption != 'n');

    NEWLINE
}

void bookAndTicket::ampOrderCreate()
{
    //take offerID & remaining PRINT details
    //create PNR & issue ticket assuming payment & mode is always provided immediately & is cash

    //local vars


    NEWLINE
    enterDetails();

    //show all details
    std::cout << "-----Entered details are as below-----"; NEWLINE
    std::cout << "Name of Passenger     : " << sName; NEWLINE
    std::cout << "Phone Number          : " << sPhoneNumber; NEWLINE
    std::cout << "Date Of Birth         : " << sDateOfBirth; NEWLINE
    std::cout << "EmailID               : " << sEmail; NEWLINE
    std::cout << "Gender                : " << cGender; NEWLINE
    std::cout << "Name of Passenger     : " << sName; NEWLINE
    std::cout << "Itinerary             : " << sItinerary; NEWLINE
    std::cout << "Offer Selected        : " << sSelectedOffer; NEWLINE
    std::cout << "Date Of Travel        : " << sTravelDate; NEWLINE
    std::cout << "Reservation Office    : " << sReservationPCC; NEWLINE
}
