// @(#)root/tmva $Id$
/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAGAexample                                                        *
 *                                                                                *
 * This exectutable gives an example of a very simple use of the genetic algorithm*
 * of TMVA                                                                        *
 *                                                                                *
 **********************************************************************************/

#include <iostream> // Stream declarations
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "TMVA/GeneticAlgorithm.h"
#include "TMVA/GeneticFitter.h"
#include "TMVA/IFitterTarget.h"
#define H 800

using namespace std;

namespace TMVA {

/*class element
{
public:
	double L;
	double C;
	double R;
	double P;
		
	double Profit;
	double Income;
	element();

	element(double LPM,double CPL,double CR,double PPS)
	{
		L = LPM;
		C = CPL;
		R = CR;
		P = PPS;
	}

	void Calculation()
	{
		Profit = L*R*P-(H+L*C);
		Income = L*R*P;		
	}
};*/
double L;
double C;
double R;
double P;
double vlma,vlmi,vcma,vcmi,vrma,vrmi,vpma,vpmi;
        
	
void Store_the_initial_value()
{
	fstream file;
	file.open("/home/wenliang/coding_class_report/Store_the_Max_Min_value.txt",ios::in);
	file>>vlma>>vlmi>>L>>vcma>>vcmi>>C>>vrma>>vrmi>>R>>vpma>>vpmi>>P;
	cout <<vlmi<<" " <<vlma<<" " << vrmi << "  " << vrma << " " <<vcmi<<" " <<vcma<<endl;

}



class MyFitness : public IFitterTarget {
    public:
       MyFitness() : IFitterTarget() {
       }
       //element E();
       // the fitness-function goes here
       // the factors are optimized such that the return-value of this function is minimized
       // take care!! the fitness-function must never fail, .. means: you have to prevent
       // the function from reaching undefined values (such as x=0 for 1/x or so)
       //
       // HINT: to use INTEGER variables, it is sufficient to cast the "factor" in the fitness-function
       // to (int). In this case the variable-range has to be chosen +1 ( to get 0..5, take Interval(0,6) )
       // since the introduction of "Interval" ranges can be defined with a third parameter
       // which gives the number of bins within the interval. With that technique discrete values
       // can be achieved easier. The random selection out of this discrete numbers is completly uniform.
       //
	    
       Double_t EstimatorFunction( std::vector<Double_t> & factors ){
		double significance;
		//double Prof_tmp;
		double Profit;
		double Income;
		Profit = factors.at(1)*factors.at(0)*(P)-(H+factors.at(1)*factors.at(2));
		Income = factors.at(1)*factors.at(0)*(P);
		/*Profit = L*factors.at(0)*(P)-(H+(L)*(C));
		Income = (L)*factors.at(0)*(P);*/
		significance = Profit/sqrt(Income);
		//significance = Profit/37500;
		return -significance;
			
       }
};


class MyGA2nd : public GeneticAlgorithm {
    public:
       MyGA2nd( IFitterTarget& target, Int_t size, vector<Interval*>& ranges ) : GeneticAlgorithm(target,
       size, ranges ){
       }


       // this method has to be activated if one wants to change the behaviour of the evolution 
       // works only with the head version
       //void Evolution(){
       //    fSexual = true;
       //    if (fSexual) {
       //       fPopulation.MakeCopies( 5 );  
       //       fPopulation.MakeChildren();
       //       fPopulation.NextGeneration();

       //       fPopulation.Mutate( 10, 3, kTRUE, fSpread, fMirror );
       //       fPopulation.Mutate( 40, fPopulation.GetPopulationSize()*3/4 );
       //    } else {
       //       fPopulation.MakeCopies( 3 );  
       //       fPopulation.MakeMutants(100,true, 0.1, true);
       //       fPopulation.NextGeneration();
       //    }
      // }
};



void exampleGA2nd(){
		//element E;
        std::cout << "\n2nd EXAMPLE" << std::endl;
        // define all the parameters by their minimum and maximum value
        // in this example 3 parameters are defined. 
        vector<Interval*> ranges;
        ranges.push_back( new Interval(vrmi,vrma,10 ));
        ranges.push_back( new Interval(vlmi,vlma,10 ));
        ranges.push_back( new Interval(vcmi,vcma,10 ));

        for( std::vector<Interval*>::iterator it = ranges.begin(); it != ranges.end(); it++ ){
           std::cout << " range: " << (*it)->GetMin() << "   " << (*it)->GetMax() << std::endl;
        }

        IFitterTarget* myFitness = new MyFitness();

        // prepare the genetic algorithm with an initial population size of 20
        // mind: big population sizes will help in searching the domain space of the solution
        // but you have to weight this out to the number of generations
        // the extreme case of 1 generation and populationsize n is equal to 
        // a Monte Carlo calculation with n tries

        MyGA2nd mg( *myFitness, 100, ranges );
       // mg.SetParameters( 4, 30, 200, 10,5, 0.95, 0.001 );

        #define CONVSTEPS 20	   
        #define CONVCRIT 0.0001
        #define SCSTEPS 10
        #define SCRATE 5
        #define SCFACTOR 0.95
        
        do {
           // prepares the new generation and does evolution
           mg.Init();

           // assess the quality of the individuals
           mg.CalculateFitness();

           mg.GetGeneticPopulation().Print(0);
//     std::cout << "---" << std::endl;
           
           // reduce the population size to the initially defined one
           mg.GetGeneticPopulation().TrimPopulation();

           // tricky thing: control the speed of how fast the "solution space" is searched through
           // this function basically influences the sigma of a gaussian around the actual value
           // of the parameter where the new value will be randomly thrown. 
           // when the number of improvements within the last SCSTEPS 
           // A) smaller than SCRATE: divide the preset sigma by SCFACTOR
           // B) equal to SCRATE: do nothing
           // C) greater than SCRATE: multiply the preset sigma by SCFACTOR
           // if you don't know what to do, leave it unchanged or even delete this function call
           mg.SpreadControl( SCSTEPS, SCRATE, SCFACTOR );

        } while (!mg.HasConverged( CONVSTEPS, CONVCRIT ));  // converged if: fitness-improvement < CONVCRIT within the last CONVSTEPS loops

        GeneticGenes* genes = mg.GetGeneticPopulation().GetGenes( 0 );
        std::vector<Double_t> gvec;
        gvec = genes->GetFactors();
        int n = 0;
        for( std::vector<Double_t>::iterator it = gvec.begin(); it<gvec.end(); it++ ){
            std::cout << "FACTOR " << n << " : " << (*it) << std::endl;
            n++;
        }
}



} // namespace TMVA

int main( int argc, char** argv ) 
{
	
	/*double Lead_per_Month,Cost_per_Lead,Conversion_Rate,Profit_per_Sale;
	//double *L,*C,*R,*P,*Profit,*Income;
	cout << "Input Lead per Month: ";
    cin >>Lead_per_Month;
    cout << "Input Cost per Lead: ";
    cin >> Cost_per_Lead;
    cout << "Input Conversion Rate: ";
    cin >> Conversion_Rate;
	cout << "Input Profit per Sale: ";
    cin >> Profit_per_Sale;
	L = &Lead_per_Month;
	C = &Cost_per_Lead;
	R = &Conversion_Rate;
	P = &Profit_per_Sale;*/

	TMVA::Store_the_initial_value();
   cout << "Start Test TMVAGAexample" << endl
        << "========================" << endl
        << endl;

   TMVA::exampleGA2nd();
}
