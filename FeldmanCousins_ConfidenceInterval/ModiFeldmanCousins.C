#include "TModiFeldmanCousins.cxx"
void ModiFeldmanCousins()
{
    if (!gROOT->GetClass("TModiFeldmanCousins"))
        R__LOAD_LIBRARY(libPhysics);
    
    TModiFeldmanCousins f;
    fstream file;
    // calculate either the upper or lower limit for 20 observed
    // events with an estimated background of 3.  The calculation of
    // either upper or lower limit will return that limit and fill
    // data members with both the upper and lower limit for you.
    Double_t Nobserved = 20;
    Double_t Nbackground = 0.001;
    Double_t ul;
    Double_t ll;
    // f.SetCL(0.90); // Set Confidence Interval 95%
    
    // 1.write in txt
    file.open("data_Modi.txt", ios::out); // open txt file, write into RAM from file mode
    
    for(int n = 0 ; n <= Nobserved; n++)
    {
       ul = f.CalculateUpperLimit(n, Nbackground);
       ll = f.GetLowerLimit();
       file << n << " " << ul << " " << ll << endl;
    }

    // file.close();

    // ul = f.CalculateUpperLimit(Nobserved, Nbackground);
    // ll = f.GetLowerLimit();

    // cout << "For " <<  Nobserved << " data observed with and estimated background"<<endl;
    // cout << "of " << Nbackground << " candidates, the Feldman-Cousins method of "<<endl;
    // cout << "calculating confidence limits gives:"<<endl;
    // cout << "\tUpper Limit = " <<  ul << endl;
    // cout << "\tLower Limit = " <<  ll << endl;
    // cout << "at the 90% CL"<< endl;
}
