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

        std::string sEmail;
        std::string sFullName;
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
        std::string ampAirShopping(std::string, std::string);
        void ampOfferPrice(std::string);
        void ampOrderCreate();
};

int main(){
    //local var
    int a = {199+1};
    std::string sTempString, sTempString2, sTempTravelDate, sTempIti;
    std::string sItiHolder;
    char cChoice = 'N';

    //code
    std::cout << a SPACE << "OK" << endl; NEWLINE

    bookAndTicket pnr1;

    NEWLINE
    std::cout << "Enter travel date (DD-MM-YYYY) : ";
    std::cin >> sTempTravelDate; NEWLINE

    std::cout << "Enter 1 way route in given format XXX-XXX : ";
    std::cin >> sTempIti; NEWLINE

    sItiHolder = pnr1.ampAirShopping(sTempIti, sTempTravelDate);

    std::cout << "Continue to Price the Offer (Y/N) ? : "; NEWLINE
    std::cin >> cChoice;

    if(cChoice == 'Y' || cChoice == 'y'){
        pnr1.ampOfferPrice(sItiHolder);
    }


    pnr1.enterDetails();
    //pnr1.ampOfferPrice();
    //pnr1.ampOrderCreate();

    return 0;
}

//function definitions
void bookAndTicket::enterDetails(){
    //local vars

    //code
    //std::cin.clear();
    //std::cin.sync();
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

std::string bookAndTicket::ampAirShopping(std::string sIti, std::string sDate)
{
    //local variable
    std::string sTempString1, sTempString2;
    std::vector<std::string> sTempVec;
    bool bAvailabilityFlag = false;

    //code
    sItinerary = sIti;

    std::cout << "--------------AIRSHOPPING RS--------------"; NEWLINE

    //open file of markets
    std::ifstream inputFile("markets.txt");                           //opening file with read mode

        //print that tempStr
        while(inputFile >> sTempString1)                               //works perfectly without any space issue in .txt file
        {
            sTempVec.push_back(sTempString1);
        }

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
            std::cout << "Below Offers Available for Route : " << sTempString2  << " for date : " << sDate << endl; NEWLINE
            //ampOfferPrice();
        }
        else{
            std::cout << "No Fares Available for Route. Try from below list." << endl; NEWLINE
            for(auto i : sTempVec){
                std::cout << i; NEWLINE
            }
        }

    inputFile.close();

    return sIti;
}

void bookAndTicket::ampOfferPrice(std::string sIti){
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

    //code
    std::cout << "--------------OFFERPRICE RS--------------"; NEWLINE

    inputFile.open("prices.txt");

    //reading prices file & pushing its strings into sTempString
    while(inputFile >> sTempString)                               //works perfectly without any space issue in .txt file
    {
        sTempVec.push_back(sTempString);
    }

    inputFile.close();

    for(auto i : sTempVec){
        std::cout << i; 
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

        /*do
        {
            std::cout << "Continue to Book & Issue Ticket (Y/N) ? : "; NEWLINE
            std::cin >> cCharOption;

            if(cCharOption == 'Y' || cCharOption == 'y'){
                std::cout << "---Creating PNR & Issuing Ticket---";
                //ampOrderCreate();
                return;
            }
        }
        while (cCharOption != 'N' || cCharOption != 'n');*/
        break;

        case 2:
        std::cout << "Accepted Offer is " << sTempVec.at(1); NEWLINE
        break;

        case 3:
        std::cout << "Accepted Offer is " << sTempVec.at(2); NEWLINE
        break;

        case 4:
        std::cout << "Accepted Offer is " << sTempVec.at(3); NEWLINE
        break;
    }

    NEWLINE
}

void bookAndTicket::ampOrderCreate()
{
    //take offerID & remaining PRINT details
    //create PNR & issue ticket assuming payment & mode is always provided immediately & is cash
    NEWLINE

    std::cout << "Inside OrderCreate"; NEWLINE

   
}
