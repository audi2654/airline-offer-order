//One class, 4 funtions - AS, OP, OC, ORet

//1. Searching for market - AS
//2. Offer generation & pricing - OP
//3. PNR Creation - OC
    
    //PNR requires 5 mandatory elements to create a reservation/booking - PRINT
    //1. Phone number
    //2. Reservation Office / Received from
    //3. Itinerary
    //4. Name of pax
    //5. Ticket issuance status/time

//4. Ticket Issuance - OC
//5. Export ticket as text file
//6. Should be able Retrieve that ticket - ORet

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::endl;

#define NEW_LINE std::cout << endl;

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
        char cGender;
        std::string sDateOfBirth;
        std::string sRecordLocator;
        unsigned int iTicketNumber;
        std::string sTicketingTime;

        //creating a constructor & initializing vars to some default values
        bookAndTicket(){
            sPhoneNumber = "9876543210";
            sReservationPCC = "FLX1";
            sItinerary = "DXB-PNQ";
            sName = "Aditya";
            bTicketingStatus = false;

            sTravelDate = "10-05-2023";
            sSelectedOffer = "PremiumClass";
            sEmail = "test@gmail.com";
            cGender = 'N';
            sDateOfBirth = "03-02-1998";
            sRecordLocator = "";
            iTicketNumber = 1234567890;
            sTicketingTime = "";
        }

        //function declarations/prototype
        void enterDetails();
        void getCurrentTime();
        void ampAirShopping();
        void ampOfferPrice();
        void ampOrderCreate();
        void ampOrderRetrieve();
};

int main(){
    //local var
    int a = {199+1};
    char cChoice = 0;

    //code
    do{
        NEW_LINE
        std::cout << "1. Create an Order & issue Ticket"; NEW_LINE
        std::cout << "2. Retrieve an booked Order"; NEW_LINE
        std::cout << "3. Exit"; NEW_LINE NEW_LINE 
        std::cout << "Enter option : ";
        std::cin >> cChoice; NEW_LINE

        bookAndTicket pnr1;

        switch(cChoice)
        {
            case '1':
            pnr1.ampAirShopping();
            break;

            case '2':
            pnr1.ampOrderRetrieve();
            break;

            case '3':
            std::cout << "Exitting"; NEW_LINE
            exit(0);
            break;

            default:
            std::cout << "Enter correct option"; NEW_LINE
            break;
        }
    }
    while(true);

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

    std::cout << "Enter Phone Number : ";
    std::getline(std::cin, sPhoneNumber);

    std::cout << "Enter Email ID : ";
    std::getline(std::cin, sEmail);

    std::cout << "Enter Date Of Birth (DD-MM-YYYY) : ";
    std::getline(std::cin, sDateOfBirth);

    std::cout << "Enter Gender (F/M) : ";
    std::cin >> cGender;
}

void bookAndTicket::getCurrentTime(){
    //local vars
    time_t currentTime;
    tm *currentTimeStruct;

    char dateBuff[100];
    char timeBuff[100];

    //code
    time(&currentTime);

    currentTimeStruct = localtime(&currentTime);

    strftime(timeBuff, 50, "%T", currentTimeStruct);
    strftime(dateBuff, 50, "%B %d %Y", currentTimeStruct);

    sTicketingTime = sTicketingTime + timeBuff + " " + dateBuff;
}

void bookAndTicket::ampAirShopping()
{
    //local variable
    std::string sTempString, sTempString2;
    std::vector<std::string> sTempVec;
    bool bAvailabilityFlag = false;

    //code
    NEW_LINE
    std::cout << "Enter travel date (DD-MM-YYYY) : ";
    std::cin >> sTravelDate; NEW_LINE

    std::cout << "Enter 1 way route in given format XXX-XXX : ";
    std::cin >> sItinerary; NEW_LINE

    std::cout << "--------------AIRSHOPPING RS--------------"; NEW_LINE

    //open file of markets
    std::ifstream inputFile("markets.txt");                           //opening file with read mode

    //pushing its strings into sTempVec
    while(inputFile >> sTempString)
    {
        sTempVec.push_back(sTempString);
    }

    //compare strings in sTempVec with itinerary string
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
        std::cout << "Below Offers Available for Route : " << sTempString2  << " for Date " << sTravelDate << endl; NEW_LINE
        ampOfferPrice();
    }
    else{
        std::cout << "No Fares Available for Route. Try from below list." << endl; NEW_LINE
        for(auto i : sTempVec){
            std::cout << i; NEW_LINE
        }
    }

    inputFile.close();
}

void bookAndTicket::ampOfferPrice(){
    //next step is to show 4 offers for sItinerary route
    //show as economy, premium economy, business & first class with Fares from classPrices.txt file
    //price them right in this RQ function & show final price to pay

    //local vars
    std::ifstream inputFile;
    std::string sTempString, sTempString2;
    std::vector<std::string> sTempVec;
    unsigned int iClassOption = 0;
    char cCharOption = 'N';
    int num = 0;

    //code
    std::cout << "--------------OFFERPRICE RS--------------"; NEW_LINE

    //reading classPrices file
    inputFile.open("classPrices.txt");

    //pushing its strings into sTempVec
    while(inputFile >> sTempString)
    {
        sTempVec.push_back(sTempString);
    }

    inputFile.close();

    for(auto i : sTempVec){
        std::cout << ++num << ". " << i; 
        NEW_LINE
    }
    NEW_LINE

    std::cout << "Enter preferred option : ";
    std::cin >> iClassOption;

    NEW_LINE
    switch(iClassOption)
    {
        case 1:
        std::cout << "Accepted Offer is " << sTempVec.at(0); NEW_LINE
        sSelectedOffer = sTempVec.at(0);
        break;

        case 2:
        std::cout << "Accepted Offer is " << sTempVec.at(1); NEW_LINE
        sSelectedOffer = sTempVec.at(1);
        break;

        case 3:
        std::cout << "Accepted Offer is " << sTempVec.at(2); NEW_LINE
        sSelectedOffer = sTempVec.at(2);
        break;

        case 4:
        std::cout << "Accepted Offer is " << sTempVec.at(3); NEW_LINE
        sSelectedOffer = sTempVec.at(3);
        break;

        default:
        std::cout << "Wrong Option Entered"; NEW_LINE
        exit(1);
    }

    do
    {
        NEW_LINE
        std::cout << "Continue to Book & Issue Ticket (Y/N) ? : ";
        std::cin >> cCharOption;

        if(cCharOption == 'Y' || cCharOption == 'y'){
            std::cout << "\n ---Creating PNR & Issuing Ticket---";
            ampOrderCreate();
            return;
        }
    }
    while (cCharOption != 'N' || cCharOption != 'n');

    NEW_LINE
}

void bookAndTicket::ampOrderCreate()
{
    //take offer & remaining PRINT details
    //create PNR & issue ticket assuming payment & mode is always provided immediately & is cash

    //local vars
    char cChoice = 'N';
    std::ofstream outputFile;
    std::string sTktNumStr;

    //code
    NEW_LINE
    enterDetails();

    //show all details
    NEW_LINE
    std::cout << "-----Entered details are as below-----"; NEW_LINE
    std::cout << "Name of Passenger     : " << sName; NEW_LINE
    std::cout << "Phone Number          : " << sPhoneNumber; NEW_LINE
    std::cout << "Date Of Birth         : " << sDateOfBirth; NEW_LINE
    std::cout << "EmailID               : " << sEmail; NEW_LINE
    std::cout << "Gender                : " << cGender; NEW_LINE
    std::cout << "Itinerary             : " << sItinerary; NEW_LINE
    std::cout << "Offer Selected        : " << sSelectedOffer; NEW_LINE
    std::cout << "Date Of Travel        : " << sTravelDate; NEW_LINE
    std::cout << "Reservation Office    : " << sReservationPCC; NEW_LINE

    NEW_LINE
    std::cout << "Default Form of Payment : CASH"; NEW_LINE
    std::cout << "Issue Documents ? (Y/N) : ";
    std::cin >> cChoice;

    NEW_LINE
    if(cChoice == 'Y' || cChoice == 'y'){
        srand(time(NULL));
        iTicketNumber = rand();

        sTktNumStr = std::to_string(iTicketNumber);

        if(iTicketNumber)
            bTicketingStatus = true;

        getCurrentTime();
        sRecordLocator = sRecordLocator + sName.at(0) + sItinerary[2] + cGender + sEmail[4] + sPhoneNumber.at(5) + sName[3];

        for(int i = 0; sRecordLocator[i] != 0; i++)
        {
            if(sRecordLocator[i] >= 'a' && sRecordLocator[i] <= 'z')
            sRecordLocator[i] -= 32;
        }
        
        std::cout << "Documents Issued Successfully"; NEW_LINE
        std::cout << "Your Record Locator (PNR) is  : " << sRecordLocator; NEW_LINE
        std::cout << "Your Ticket Number is         : " << iTicketNumber; NEW_LINE
    }
    NEW_LINE

    if(bTicketingStatus == true){
        outputFile.open(sRecordLocator + ".txt");
        std::string temp;

        temp = "Electronic Ticket\n"
                "Status: Ticketed\n"
                "--------------------------------------------Ticket Image--------------------------------------------\n" 
                "| AGY        : " + sReservationPCC + "                           O/D    : " + sItinerary + "           FF No   :                 |\n"
                "| ISSUED     : " + sTicketingTime + "      TKT    : " + sTktNumStr + "         AGT     : apanchal        |\n"
                "| PNR        : " + sRecordLocator + "                         IATA   : 71752214" + "                                    |\n"
                "----------------------------------------------------------------------------------------------------\n";
        
        outputFile << temp;
        outputFile.close();
    }

    NEW_LINE
}

void bookAndTicket::ampOrderRetrieve(){
    //local vars
    std::ifstream inputFile;
    std::string sTempRecLoc;
    std::string sTempString;
    std::vector<std::string> sTempVec;

    //code
    std::cout << "Enter Record Locator to open : ";
    std::cin >> sTempRecLoc;
    inputFile.open(sTempRecLoc + ".txt");

    NEW_LINE

    if(inputFile)
    {
        while(!inputFile.eof())
        {
            std::getline(inputFile, sTempString);
            std::cout << sTempString;
        }

        for(auto i : sTempVec){
            std::cout << i; NEW_LINE
        }
    }

    inputFile.close();

    NEW_LINE;
}
