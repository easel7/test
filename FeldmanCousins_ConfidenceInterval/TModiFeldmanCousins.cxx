/** \class TModiFeldmanCousins
 \ingroup Physics


#### VARIABLES THAT CAN BE ALTERED
=> depending on your desired precision: The initial values of fMuMin,
fMuMax, fMuStep and fNMax are those used in the PRD:
~~~ {.cpp}
fMuMin = 0.0
fMuMax = 50.0
fMuStep= 0.005
~~~
**/

#include <iostream>
#include "TMath.h"
#include "TModiFeldmanCousins.h"


ClassImp(TModiFeldmanCousins);

////////////////////////////////////////////////////////////////////////////////
/// Constructor.

TModiFeldmanCousins::TModiFeldmanCousins(Double_t newFC, TString options)
{
   fCL          = newFC;
   fUpperLimit  = 0.0;
   fLowerLimit  = 0.0;
   fNobserved   = 0.0;
   fNbackground = 0.0;
   options.ToLower();
   if (options.Contains("q")) fQUICK = 1;
   else                       fQUICK = 0;

   fNMax   = 50;
   fMuStep = 0.005;
   SetMuMin();
   SetMuMax();
   SetMuStep();
}


////////////////////////////////////////////////////////////////////////////////
// Destructor.

TModiFeldmanCousins::~TModiFeldmanCousins()
{
}

////////////////////////////////////////////////////////////////////////////////
/// given Nobserved and Nbackground, try different values of mu that give lower limits that
/// are consistent with Nobserved.  The closed interval (plus any stragglers) corresponds
/// to the F&C interval

Double_t TModiFeldmanCousins::CalculateLowerLimit(Double_t Nobserved, Double_t Nbackground)
{
   CalculateUpperLimit(Nobserved, Nbackground);
   return fLowerLimit;
}


////////////////////////////////////////////////////////////////////////////////
/// given Nobserved and Nbackground, try different values of mu that give upper limits that
/// are consistent with Nobserved.  The closed interval (plus any stragglers) corresponds
/// to the F&C interval

Double_t TModiFeldmanCousins::CalculateUpperLimit(Double_t Nobserved, Double_t Nbackground)
{
   fNobserved   = Nobserved;
   fNbackground = Nbackground;

   Double_t mu = 0.0;

   // for each mu construct the ranked table of probabilities and test the
   // observed number of events with the upper limit
   Double_t min = -999.0;
   Double_t max = 0;
   Int_t iLower = 0;

   Int_t i;
   for(i = 0; i <= fNMuStep; i++) {
      mu = fMuMin + (Double_t)i*fMuStep;
      Int_t goodChoice = FindLimitsFromTable( mu );
      //cout << mu << endl;
      if( goodChoice ) {
            min = mu;
            iLower = i;
            //cout << "break" << mu << endl;
            break;
      }
   }

   //==================================================================
   // For quicker evaluation, assume that you get the same results when
   // you expect the uppper limit to be > Nobserved-Nbackground.
   // This is certainly true for all of the published tables in the PRD
   // and is a reasonable assumption in any case.
   //==================================================================

   Double_t quickJump = 0.0;
   if (fQUICK)          quickJump = Nobserved-Nbackground-fMuMin;
   if (quickJump < 0.0) quickJump = 0.0;

   for(i = iLower+1; i <= fNMuStep; i++) {
      mu = fMuMin + (Double_t)i*fMuStep + quickJump;
      Int_t goodchoice = FindLimitsFromTable( mu ); // goodChoice = goodchoicec
      //  cout << goodchoice << " " << mu << endl;
      if( !goodchoice ) {
         max = mu;
      //  cout << "break" << mu << endl;
         break;
      }
   }

   fUpperLimit = max;
   fLowerLimit = min;
   
   return max;
}

////////////////////////////////////////////////////////////////////////////////
/// calculate the probability table for a given mu for n = 0, NMAX
/// and return 1 if the number of observed events is consistent
/// with the CL bad

Int_t TModiFeldmanCousins::FindLimitsFromTable( Double_t mu )
{
   Double_t *p          = new Double_t[fNMax];   //the array of probabilities in the interval MUMIN-MUMAX
   Double_t *r          = new Double_t[fNMax];   //the ratio of likliehoods = P(Mu|Nobserved)/P(MuBest|Nobserved)
   Int_t    *rank       = new Int_t[fNMax];      //the ranked array corresponding to R (largest first)
   Double_t *muBest     = new Double_t[fNMax];
   Double_t *probMuBest = new Double_t[fNMax];

      //calculate P(i | mu) and P(i | mu)/P(i | mubest)
      //exactly k events total given at most n background events  
      Int_t i; // n
      // nobserved = n0
      for(i = 0; i < fNMax; i++) 
      {
         // muBest[i] = i - fNbackground;
         if((fNobserved >= fNbackground) && (i >= fNbackground))
         {
            muBest[i] = i - fNbackground; // Condition Probabality Xiongzheng
         }
         else if((fNobserved < fNbackground) && (i >= fNobserved))
         {
            muBest[i] = i - fNobserved; // Condition Probabality Xiongzheng
         }
         else
         {
            muBest[i] = 0.0; // Condition Probabality Xiongzheng
         }
         probMuBest[i] = Prob(i, muBest[i],  fNbackground, fNobserved); // Condition Probabality Xiongzheng
         p[i]          = Prob(i, mu,  fNbackground, fNobserved); // Condition Probabality Xiongzheng
         if(probMuBest[i] == 0.0) r[i] = 0.0;
         else                     r[i] = p[i]/probMuBest[i];
      }
   
   

      //rank the likelihood ratio
      TMath::Sort(fNMax, r, rank);

      //search through the probability table and get the i for the CL
      Double_t sum = 0.0;
      Int_t iMax = rank[0];
      Int_t iMin = rank[0];
      for(i = 0; i < fNMax; i++) {
         sum += p[rank[i]];
      
         if(iMax < rank[i]) iMax = rank[i];
         if(iMin > rank[i]) iMin = rank[i];
         if(sum >= fCL) break;
      }

      delete [] p;
      delete [] r;
      delete [] rank;
      delete [] muBest;
      delete [] probMuBest;

      // cout<< sum << " "<< mu << " "<< iMin << " " << iMax << endl;
      if((fNobserved <= iMax) && (fNobserved >= iMin))   return 1; // n1 <= fNobserved <= n2
      else  return 0; 
   
}

////////////////////////////////////////////////////////////////////////////////
/// Calculate the poissonian probability for a mean of mu+B events with a variance of N.

Double_t TModiFeldmanCousins::Prob(Int_t k, Double_t mu, Double_t B, Double_t N) // Condition Probabality Xiongzheng 
{
   // return TMath::Poisson( k, mu+B)/ROOT::Math::poisson_cdf( k, B);	
   Double_t sum = 0;
   if(k <= N)
   {
      sum = TMath::Poisson( k, mu+B )/ROOT::Math::poisson_cdf( N, B);
      return sum; 
   }
   else	
   {
      for(Int_t j = 0; j <= N ; j++ )
      {
         sum = sum + (TMath::Poisson( j, B) * TMath::Poisson( k-j, mu)) / ROOT::Math::poisson_cdf( N, B);
      }
      return sum;
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Set maximum value of signal to use in calculating the tables.

void TModiFeldmanCousins::SetMuMax(Double_t newMax)
{
   fMuMax   = newMax;
   fNMax    = (Int_t)newMax;
   SetMuStep(fMuStep);
}

////////////////////////////////////////////////////////////////////////////////
/// Set the step in signal to use when generating tables.

void TModiFeldmanCousins::SetMuStep(Double_t newMuStep)
{
   if(newMuStep == 0.0) {
      std::cout << "TModiFeldmanCousins::SetMuStep ERROR New step size is zero - unable to change value"<< std::endl;
      return;
   } else {
      fMuStep = newMuStep;
      fNMuStep = (Int_t)((fMuMax - fMuMin)/fMuStep);
   }
}
